/**
*  @file    SpawnPoint.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    12/05/2018
*  @version v1.0
*
*  @section System Module
*           Gameplay
*
*  @brief Defines a point where spwans can occur.
*
*  @section Description
*  Simply a position in space where players are spawned. These objects tell the players where to spawn and is used by the
*  game manager to place players. These players are then spawned at the said points and can be changed at any time.
*  
*/


#pragma once

#include "pch.h"

class SpawnPoint : public GameObject2D 
{
public:
	SpawnPoint(Vector2 position);
	~SpawnPoint() = default;


	// Inherited via GameObject2D
	virtual void CentreOrigin() override;

	virtual void Tick(GameStateData * _GSD) override;

	virtual void Render(RenderData * _RD) override;

};