#pragma once

// TODO - Add headers for the constructors which are then called 
#include <jsoncons\json.hpp>
#include "RenderData.h"

#include "Obstacle2D.h"


namespace Entities 
{
	// TODO - Create class of initialisation routienes.
	static GameObject2D* constructPlayer(RenderData* _RD, jsoncons::key_value_pair<std::string, jsoncons::json> key)
	{
		return new Obstacle2D(_RD, key.value()["filename"].as_string());
	}
}