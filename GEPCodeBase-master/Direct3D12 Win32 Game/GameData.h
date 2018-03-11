/**
*  @file    GameData.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    11/03/2018
*  @version v1.0
*
*  @section System Module
*           Gameplay Management.
*
*  @brief Definition for the GameData structure
*
*  @section Description
*
*  Defines the GameData structure which is risponcable for managing the 
*/


#pragma once

struct GameData 
{
	// TODO - Add any additional settings to the field here. 
	int game_length = 3000;
	int game_speed_multiplier = 1;
	int game_knockback_multiplier = 1;
};