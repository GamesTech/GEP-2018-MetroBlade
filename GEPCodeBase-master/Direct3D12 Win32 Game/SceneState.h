#pragma once

#include "pch.h"
#include "SceneEvent.h"

class SceneState 
{
public:
	SceneState() = default; 
	~SceneState() = default;

	void assignSceneManagerListener(std::shared_ptr<SceneEvent>   event_ref);

	// Interface
	void changeScene(std::string   new_scene_name);
	void pauseGame();
	void exitGame();

private:
	std::shared_ptr<SceneEvent>		world_event_data;
};
