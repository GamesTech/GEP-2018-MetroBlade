/**
*  @file    SceneLoader.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    06/05/2018
*  @version v1.0
*
*  @section System Module
*           Scene Management
*
*  @brief Scene loading function delegates
*
*  @section Description
*
*  Defines a set of constructor functions which can be used to create objects.
*
*/

#pragma once

// TODO - Add headers for the constructors which are then called 
#include <jsoncons\json.hpp>
#include "RenderData.h"


// Object Entity Headers - (Additional Constructors should be added here).
#include "Obstacle2D.h"
#include "SpawnPoint.h"
#include "Spawner.h"


// TODO - Add information into functions to properly setup the objects according to specified parameters.

namespace Entities 
{
	// TODO - Create class of initialisation routienes.
	static GameObject2D* constructObstacle2D(RenderData* _RD, jsoncons::key_value_pair<std::string, jsoncons::json> key)
	{
		GameObject2D* test = new Obstacle2D(_RD, key.value()["filename"].as_string());
		test->SetPos(Vector2(500, 600));
		return test;
	}

	// Utility Objects
	static GameObject2D* constructSpawnPoint(RenderData* _RD, jsoncons::key_value_pair<std::string, jsoncons::json> key) 
	{
		return new SpawnPoint(Vector2(key.value()["position"][0].as_double(), key.value()["position"][1].as_double()));
	}

	static GameObject2D* constructItemSpawner(RenderData* _RD, jsoncons::key_value_pair<std::string, jsoncons::json> key)
	{
		return new Spawner(_RD,"",Vector2(key.value()["position"][0].as_double(), key.value()["position"][1].as_double()), (int)key.value()["item-count"].as_int());
	}
}