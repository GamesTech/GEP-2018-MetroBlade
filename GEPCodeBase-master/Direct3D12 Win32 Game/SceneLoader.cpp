#include "pch.h"
#include "SceneLoader.h"

#include "Scene.h"

#include "EntityConstructors.h"

// Here we will setup our functionptr constructors. 
// Add links to the entities in the game. 

void SceneLoader::init(RenderData * _RD)
{
	using namespace std::placeholders;
	render_data = _RD;
	addObjectInitialiser("Obstacle2D", std::bind(&SceneLoader::constructPlayer, this, _1, _2));
}

Scene* SceneLoader::createScene(std::string scene_name)
{
	file_reader.setFilePath(scene_name);
	Scene*  new_scene = nullptr;

	if (file_reader.parseFile()) 
	{
		// Here we create and load the scene. 
		new_scene = new Scene;
		constructScene(new_scene);
	}

	return new_scene;
}

void SceneLoader::addObjectInitialiser(std::string name, std::function<GameObject2D*(RenderData*, jsoncons::key_value_pair<std::string, jsoncons::json>)> constructor)
{
	object_constructors.emplace(name, constructor);
}

void SceneLoader::constructScene(Scene* scene)
{
	// Go through the list and construct the corrisponding object.
}
