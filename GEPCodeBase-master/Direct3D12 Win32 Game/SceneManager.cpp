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

void SceneManager::assignGPUControlObjects(ID3D12CommandQueue * command_queue, 
										   ID3D12Fence * fence, 
										   UINT* backbuffer_index, 
										   Microsoft::WRL::Wrappers::Event * fence_event, 
										   UINT64* fence_values)
{
	gpu_reset_object.gpu_command_queue = command_queue;
	gpu_reset_object.gpu_fence = fence;
	gpu_reset_object.backbuffer_index = backbuffer_index;
	gpu_reset_object.fence_events = fence_event;
	gpu_reset_object.fence_values = fence_values;
}

void SceneManager::Init()
{
	current_scene = new Scene;

	// Currently in test mode only
	Camera* camera = new Camera(static_cast<float>(800), static_cast<float>(600), 1.0f, 1000.0f);
	setMainCamera(camera);
	current_scene->add3DGameObjectToScene(camera);
	//m_3DObjects.push_back(camera);

	//TestPBGO3D* test3d = new TestPBGO3D();
	//test3d->SetScale(5.0f);
	//test3d->Init();
	//current_scene->add3DGameObjectToScene(test3d);
	////m_3DObjects.push_back(test3d);

	GPGO3D* test3d2 = new GPGO3D(GP_TEAPOT);
	test3d2->SetPos(10.0f*Vector3::Forward + 5.0f*Vector3::Right + Vector3::Down);
	test3d2->SetScale(5.0f);
	current_scene->add3DGameObjectToScene(test3d2);//m_3DObjects.push_back(test3d2);

	//ImageGO2D *test = new ImageGO2D(render_data, "twist");
	//test->SetOri(45);
	//test->SetPos(Vector2(300, 300));
	//test->CentreOrigin();
	//current_scene->add2DGameObjectToScene(test);//m_2DObjects.push_back(test);
	//test = new ImageGO2D(render_data, "guides_logo");
	//test->SetPos(Vector2(100, 100));
	//test->SetScale(Vector2(1.0f, 0.5f));
	//test->SetColour(Color(1, 0, 0, 1));
	//current_scene->add2DGameObjectToScene(test);//m_2DObjects.push_back(test);

	//Text2D * test2 = new Text2D("testing text");
	//current_scene->add2DGameObjectToScene(test2);//m_2DObjects.push_back(test2);

	//Player2D* testPlay = new Player2D(render_data, "gens");
	//testPlay->SetDrive(100.0f);
	//testPlay->SetDrag(0.5f);
	//current_scene->add2DGameObjectToScene(testPlay);//m_2DObjects.push_back(testPlay);

	//SDKMeshGO3D *test3 = new SDKMeshGO3D(render_data, "cup");
	//test3->SetPos(12.0f*Vector3::Forward + 5.0f*Vector3::Left + Vector3::Down);
	//test3->SetScale(5.0f);
	//current_scene->add3DGameObjectToScene(test3); //m_3DObjects.push_back(test3);
}

void SceneManager::Update(GameStateData * game_state)
{

	if (current_scene)
	{
		current_scene->Update(game_state);
	}
}

void SceneManager::Render(ID3D12GraphicsCommandList* command_list)
{
	if (current_scene) 
	{
		render_data->m_effect->SetProjection(main_camera->GetProj());
		render_data->m_effect->SetView(main_camera->GetView());
		render_data->m_effect->Apply(command_list);
		render_data->m_effect->EnableDefaultLighting();
		render_data->m_GPeffect->SetProjection(main_camera->GetProj());
		render_data->m_GPeffect->SetView(main_camera->GetView());
		current_scene->Render(render_data, command_list);
	}

	//render_data->m_batch->Begin(command_list);
	//for (std::vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	//{
	//	if ((*it)->GetType() == GO3D_RT_PRIM)(*it)->Render(render_data);
	//}
	//render_data->m_batch->End();

	////Render Geometric Primitives
	//render_data->m_GPeffect->Apply(command_list);
	//for (std::vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	//{
	//	if ((*it)->GetType() == GO3D_RT_GEOP)(*it)->Render(render_data);
	//}

	////Render VBO Models	
	//for (std::vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	//{
	//	if ((*it)->GetType() == GO3D_RT_SDK)(*it)->Render(render_data);
	//}

	////finally draw all 2D objects
	//ID3D12DescriptorHeap* heaps[] = { render_data->m_resourceDescriptors->Heap() };
	//command_list->SetDescriptorHeaps(_countof(heaps), heaps);
	//render_data->m_spriteBatch->Begin(command_list);

	//for (std::vector<GameObject2D *>::iterator it = m_2DObjects.begin(); it != m_2DObjects.end(); it++)
	//{
	//	(*it)->Render(render_data);
	//}

	//render_data->m_spriteBatch->End();
}

void SceneManager::loadScene(string scene_name)
{
	// TODO - Add Code to load diffrent Scenes into the game.
}

void SceneManager::loadScene(Scene * scene_name)
{
	current_scene = scene_name;
}

void SceneManager::clearScene()
{
	if (current_scene) 
	{
		delete current_scene;
		current_scene = nullptr;
	    setMainCamera(nullptr);
		new_scene = true;
		waitForGPU(); // Have the GPU complete all work and flush command buffers.
	}
}

void SceneManager::setMainCamera(Camera* viewport_camera)
{
	main_camera = viewport_camera;
	render_data->m_cam = main_camera;
}

void SceneManager::waitForGPU() noexcept
{
	// Here we wait for the GPU
	if (gpu_reset_object.gpu_command_queue && gpu_reset_object.gpu_fence && gpu_reset_object.fence_events->IsValid())
	{
		// Schedule a Signal command in the GPU queue.
		UINT64 fenceValue = gpu_reset_object.fence_values[*gpu_reset_object.backbuffer_index];
		if (SUCCEEDED(gpu_reset_object.gpu_command_queue->Signal(gpu_reset_object.gpu_fence, fenceValue)))
		{
			// Wait until the Signal has been processed.
			if (SUCCEEDED(gpu_reset_object.gpu_fence->SetEventOnCompletion(fenceValue, gpu_reset_object.fence_events)))
			{
				WaitForSingleObjectEx(gpu_reset_object.fence_events, INFINITE, FALSE);

				// Increment the fence value for the current frame.
				gpu_reset_object.fence_values[*gpu_reset_object.backbuffer_index]++;
			}
		}
	}
}
