




#pragma once

// TODO - Add headers for the constructors which are then called 
#include <jsoncons\json.hpp>
#include "RenderData.h"

#include "Obstacle2D.h"


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
}