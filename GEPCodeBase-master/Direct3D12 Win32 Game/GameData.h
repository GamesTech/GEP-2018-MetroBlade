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
*  Defines the GameData structure which is risponcable for managing the game configuration such as the length of the game.
*/


#pragma once

// Game Constants
constexpr int GAME_INFINITE_LIVES = -1;
constexpr int GAME_INFINITE_TIME = -1;

struct GameData 
{
	// TODO - Add any additional settings to the field here. 
	float game_length = 60.0f; ///< Game Length In Secounds
	float respawn_time = 2.0f;  ///< time before respawn.
	int game_speed_multiplier = 1; ///< Speed multiplier
	int game_knockback_multiplier = 1; ///< Knockback multiplier
	int number_of_lives = GAME_INFINITE_LIVES; ///< Number of stocks that the players have.
};