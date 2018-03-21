/**
*  @file    PlayerData.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    11/03/2018
*  @version v1.0
*
*  @section System Module
*           Gameplay Management.
*
*  @brief Definition for the PlayerData structure
*
*  @section Description
*
*  Defines the PlayerData structure which holds on to critical information about the players utalised in the game. 
*/


#pragma once

#include "pch.h"




struct PlayerData 
{
	std::string   player_name = "player_null";
	std::string	  character_name = "none";
	int			  character_costume = 0;
	int			  input_device_id = 0;
};