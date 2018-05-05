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

	void init();

	Scene*   createScene(std::string scene_name);

	static void addObjectInitialiser(std::string name, std::function<void(jsoncons::key_value_pair<std::string, jsoncons::json>)> constructor);

private:
	JSONFileReader   file_reader;

	void constructScene(Scene*  scene);

private:
	// Global initialiser object.
	static std::map<std::string, std::function<void(jsoncons::key_value_pair<std::string, jsoncons::json>)>> object_constructors;
};