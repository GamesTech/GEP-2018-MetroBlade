/**
*  @file    SceneLoader.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    14/03/2018
*  @version v1.0
*
*  @section System Module
*           Scene Management 
*
*  @brief Definition for Scene Loading System.
*
*  @section Description
*
*  Defines a Scene Loader which reads a JSON style file and initialises objects according to the data in the file.
*
*/


#pragma once

#include "pch.h"

#include <map>
#include <functional>

#include "JSONFileReader.h"


class Scene;

class SceneLoader 
{
public:
	SceneLoader() = default;
	~SceneLoader() = default;

	void init(RenderData* _RD);

	Scene*   createScene(std::string scene_name);

	void addObjectInitialiser(std::string name, std::function<GameObject2D*(RenderData*, jsoncons::key_value_pair<std::string, jsoncons::json>)> constructor);

private:
	RenderData * render_data = nullptr;
	JSONFileReader   file_reader;

	void constructScene(Scene*  scene);

private:
	// Global initialiser object.
	std::map<
	std::string, 
	std::function<GameObject2D*(RenderData*,jsoncons::key_value_pair<std::string, jsoncons::json>)> 
	> object_constructors;

	GameObject2D* constructPlayer(RenderData* _RD, jsoncons::key_value_pair<std::string, jsoncons::json> key)
	{
		return new Obstacle2D(_RD, key.value()["filename"].as_string());
	}
};