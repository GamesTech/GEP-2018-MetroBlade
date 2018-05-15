#include "pch.h"
#include "SceneState.h"
#include "SceneManager.h"
#include "GameObject2D.h"
void SceneState::assignSceneManagerListener(std::shared_ptr<SceneEvent> event_ref)
{
	world_event_data = event_ref;
}

void SceneState::changeScene(std::string new_scene_name)
{
	world_event_data->event_flag = SceneEventFlags::EVENT_SIGCHANGE;
	world_event_data->new_map = new_scene_name;
}

void SceneState::pauseGame()
{
	world_event_data->event_flag = SceneEventFlags::EVENT_SIGPAUSE;
}

void SceneState::exitGame()
{
	world_event_data->event_flag = SceneEventFlags::EVENT_SIGEXIT;
}

void SceneState::panic()
{
	world_event_data->event_flag = SceneEventFlags::EVENT_SIGKILL;
}

void SceneState::assignSceneManager(SceneManager* manager)
{
	scene_manager = manager;
}

void SceneState::instantiateToScene(GameObject2D* obj)
{
	scene_manager->instanciate2DObject(obj);
}


