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
*  Scene Manager is the component that is risponcable for controlling what scene is ticked and rendered. Scene manager is 
*  risponcable for all Scene managment events such as loading new scenes.
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
	// Create a basic scene and set up all of the scene manager systems.
	game_manager.init();
	game_manager.addWorldEventListener(scene_event_listener);
	game_ui.addWorldEventListener(scene_event_listener);
	current_scene.reset(new Scene);

	Camera* camera = new Camera(static_cast<float>(800), static_cast<float>(600), 1.0f, 1000.0f);
	setMainCamera(camera);
	current_scene->add3DGameObjectToScene(camera);
}

void SceneManager::Update(GameStateData * game_state)
{
	game_manager.tickGameManager(game_state);
	if (current_scene)
	{
		current_scene->Update(game_state);
	}
	game_ui.tickUIObjects(game_state);
	processSceneEvents();
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
	game_ui.renderUIObjects(render_data);
}

bool SceneManager::shouldQuit() const
{
	return quit;
}

Scene * SceneManager::getScene()
{
	return current_scene.get();
}

void SceneManager::loadScene(string scene_name)
{
	// TODO - Add Code to load diffrent Scenes into the game.
}

void SceneManager::loadScene(Scene * scene_name)
{
	clearScene();
	game_manager.resetManager();
	game_manager.setupGame();
	current_scene.reset(scene_name);
	game_manager.startGame();
}

void SceneManager::clearScene()
{
	if (current_scene) 
	{
		resetRenderState();
		current_scene.reset(nullptr);
	    setMainCamera(nullptr);
	}
}

void SceneManager::setMainCamera(Camera* viewport_camera)
{
	main_camera = viewport_camera;
	render_data->m_cam = main_camera;
}

void SceneManager::instanciate2DObject(GameObject2D* new_object)
{
	new_object->assignWorldEventListener(scene_event_listener);
	if (dynamic_cast<Player2D*>(new_object)) 
	{
		game_manager.registerPlayer((Player2D*)new_object);
	}
	current_scene->add2DGameObjectToScene(new_object);
}

void SceneManager::instanciate3DObject(GameObject3D* new_object)
{
	new_object->assignWorldEventLisener(scene_event_listener);
	current_scene->add3DGameObjectToScene(new_object);
}

void SceneManager::instanciateUIObject(UIObject * new_object)
{
	game_ui.addUIObject(new_object);
}

void SceneManager::processSceneEvents()
{
	switch (scene_event_listener->event_flag) 
	{
		case SceneEventFlags::EVENT_SIGEXIT:
		{
			quit = true;
			break;
		}
		case SceneEventFlags::EVENT_SIGKILL:
		{
			std::cout << "Critical Error - Game Killed by EVENT_SIGKILL" << std::endl;
		
#ifdef _DEBUG
			OutputDebugString(L"Critical Error - Game Killed by event SIGKILL");
#endif 
			break;
		}
	}
	scene_event_listener->event_flag = EVENT_SIGNONE;
}

void SceneManager::resetRenderState()
{
	// Add any other resetting routienes here.
	render_data->m_resourceCount = 0;
}
