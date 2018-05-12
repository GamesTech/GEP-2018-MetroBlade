#pragma once

#include "pch.h"
#include "SceneEvent.h"

class GameObject2D;
class SceneManager;
class SceneState 
{
public:
	SceneState() = default; 
	~SceneState() = default;

	void assignSceneManagerListener(std::shared_ptr<SceneEvent>   event_ref);
	void assignSceneManager(SceneManager* manager);
	void instantiateToScene(GameObject2D* obj);
	// Interface
	void changeScene(std::string   new_scene_name);
	void pauseGame();
	void exitGame();

	void panic();  ///< Call this if an error in a game critical component occurs.

private:
	std::shared_ptr<SceneEvent>		world_event_data;
	SceneManager* scene_manager = nullptr;
};
