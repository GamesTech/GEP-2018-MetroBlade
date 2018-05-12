#pragma once
#include "pch.h"

//GEP:: Basic data of current GameState to communicate to all Game Objects

#include "MetroBrawlInputManager.h"

struct GameStateData
{
	//length of time since last frame
	MetroBrawlInputManager*   input;
	float m_dt;
};
