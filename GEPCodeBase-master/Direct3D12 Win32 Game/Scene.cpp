/**
*  @file    Scene.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    14/02/2018
*  @version v1.0
*
*  @section System Module
*           Core State Manager.
*
*  @brief Scenes Source file.
*/


#include "pch.h"

#include "RenderData.h"
#include "Scene.h"

Scene::~Scene()
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


void Scene::Update(GameStateData* game_state)
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

void Scene::Render(RenderData * render_data, ID3D12GraphicsCommandList * command_list)
{
	render_data->m_batch->Begin(command_list);
	for (std::vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		if ((*it)->GetType() == GO3D_RT_PRIM)(*it)->Render(render_data);
	}
	render_data->m_batch->End();

	//Render Geometric Primitives
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

void Scene::add2DGameObjectToScene(GameObject2D * new_object)
{
	m_2DObjects.push_back(new_object);
}

void Scene::add3DGameObjectToScene(GameObject3D * new_object)
{
	m_3DObjects.push_back(new_object);
}

bool Scene::isLevel() const
{
	return is_level;
}

void Scene::isLevel(bool level)
{
	is_level = level;
}

