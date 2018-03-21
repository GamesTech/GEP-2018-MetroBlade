/**
*  @file    PlayerController.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    11/03/2018
*  @version v1.0
*
*  @section System Module
*           Game Mode Setup.
*
*  @brief Handles Player registration for game objects and other components.
*
*  @section Description
*
*  Defines an interface which game objects can use to create and deleate players from the game. Utalised in the title screen 
*  for detecting players and then allocating there costumes etc.
*/


#pragma once

#include "GameComponent.h"
#include "PlayerData.h"

class PlayerController : public GameComponent 
{
public:
	PlayerController(std::vector<PlayerData>* player_register);
	~PlayerController() = default;

	// Inherited via GameComponent
	void tickComponent(GameStateData * _GSD) override;
	void renderComponent(RenderData * _RD) override;

private:
	std::vector<PlayerData>*	player_data_buffer = nullptr;
};