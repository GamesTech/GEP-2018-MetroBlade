#include "pch.h"
#include "SceneLoader.h"

#include "Scene.h"

// Here we will setup our functionptr constructors. 


void SceneLoader::init()
{

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

void SceneLoader::addObjectInitialiser(std::string name, std::function<void(jsoncons::key_value_pair<std::string, jsoncons::json>)> constructor)
{
	// object_constructors.emplace(name, constructor);
}

void SceneLoader::constructScene(Scene* scene)
{
	// Go through the list and construct the corrisponding object.
}
