/**
*  @file    SceneManager.cpp
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    13/02/2018
*  @version v1.0
*
*  @section System Module
*           Core State Manager.
*
*  @brief Scene Manager system that handles the updating and rendering of levels.
*
*  @section Description
*
*  (Add a lengthy discription here of the source file.)
*/

#include "pch.h"

#include "RenderData.h"
#include "StepTimer.h"
#include "GameStateData.h"

#include "SceneManager.h"

SceneManager::SceneManager(RenderData* render_structure)
	:render_data(render_structure)
{
	Init();
}

void SceneManager::assignRenderData(RenderData* render_structure)
{
	render_data = render_structure;
}

void SceneManager::Init()
{
	// Currently in test mode only
	Camera* camera = new Camera(static_cast<float>(800), static_cast<float>(600), 1.0f, 1000.0f);
	setMainCamera(camera);
	m_3DObjects.push_back(camera);

	TestPBGO3D* test3d = new TestPBGO3D();
	test3d->SetScale(5.0f);
	test3d->Init();
	m_3DObjects.push_back(test3d);

	GPGO3D* test3d2 = new GPGO3D(GP_TEAPOT);
	test3d2->SetPos(10.0f*Vector3::Forward + 5.0f*Vector3::Right + Vector3::Down);
	test3d2->SetScale(5.0f);
	m_3DObjects.push_back(test3d2);

	ImageGO2D *test = new ImageGO2D(render_data, "twist");
	test->SetOri(45);
	test->SetPos(Vector2(300, 300));
	test->CentreOrigin();
	m_2DObjects.push_back(test);
	test = new ImageGO2D(render_data, "guides_logo");
	test->SetPos(Vector2(100, 100));
	test->SetScale(Vector2(1.0f, 0.5f));
	test->SetColour(Color(1, 0, 0, 1));
	m_2DObjects.push_back(test);

	Text2D * test2 = new Text2D("testing text");
	m_2DObjects.push_back(test2);

	Player2D* testPlay = new Player2D(render_data, "gens");
	testPlay->SetDrive(100.0f);
	testPlay->SetDrag(0.5f);
	m_2DObjects.push_back(testPlay);

	SDKMeshGO3D *test3 = new SDKMeshGO3D(render_data, "cup");
	test3->SetPos(12.0f*Vector3::Forward + 5.0f*Vector3::Left + Vector3::Down);
	test3->SetScale(5.0f);
	m_3DObjects.push_back(test3);
}

void SceneManager::Update(GameStateData* game_state)
{
	//Add your game logic here.
	for (std::vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		(*it)->Tick(game_state);
	}

	for (std::vector<GameObject2D *>::iterator it = m_2DObjects.begin(); it != m_2DObjects.end(); it++)
	{
		(*it)->Tick(game_state);
	}
}

void SceneManager::Render(ID3D12GraphicsCommandList* command_list)
{
	render_data->m_effect->SetProjection(main_camera->GetProj());
	render_data->m_effect->SetView(main_camera->GetView());
	render_data->m_effect->Apply(command_list);
	render_data->m_effect->EnableDefaultLighting();
	render_data->m_batch->Begin(command_list);
	for (std::vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		if ((*it)->GetType() == GO3D_RT_PRIM)(*it)->Render(render_data);
	}
	render_data->m_batch->End();

	//Render Geometric Primitives
	render_data->m_GPeffect->SetProjection(main_camera->GetProj());
	render_data->m_GPeffect->SetView(main_camera->GetView());
	render_data->m_GPeffect->Apply(command_list);
	for (std::vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		if ((*it)->GetType() == GO3D_RT_GEOP)(*it)->Render(render_data);
	}

	//Render VBO Models	
	for (std::vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		if ((*it)->GetType() == GO3D_RT_SDK)(*it)->Render(render_data);
	}

	//finally draw all 2D objects
	ID3D12DescriptorHeap* heaps[] = { render_data->m_resourceDescriptors->Heap() };
	command_list->SetDescriptorHeaps(_countof(heaps), heaps);
	render_data->m_spriteBatch->Begin(command_list);

	for (std::vector<GameObject2D *>::iterator it = m_2DObjects.begin(); it != m_2DObjects.end(); it++)
	{
		(*it)->Render(render_data);
	}

	render_data->m_spriteBatch->End();
}

void SceneManager::loadScene(string scene_name)
{

}

void SceneManager::clearScene()
{
	//delete the GO2Ds
	for (std::vector<GameObject2D *>::iterator it = m_2DObjects.begin(); it != m_2DObjects.end(); it++)
	{
		delete (*it);
	}
	m_2DObjects.clear();
	//delete the GO3Ds
	for (std::vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		delete (*it);
	}
	m_3DObjects.clear();
}

void SceneManager::setMainCamera(Camera* viewport_camera)
{
	main_camera = viewport_camera;
	render_data->m_cam = main_camera;
}
