/**
*  @file    ArcadeController.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    10/05/2018
*  @version v1.0
*
*  @section System Module
*           Input
*
*  @brief Definition for An Arcade Controller.
*
*  @section Description
*  Defines an arcade controller device which is used by the ArcadeControllerModule for input recognition on the 
*  arcade cabinet. 
*/

#pragma once


#include "pch.h"
#include <map>

#include "InputBind.h"


class ArcadeController 
{
public:
	ArcadeController();

	void loadMap(std::map<DirectX::Keyboard::Keys, MetroBrawlInputActions>  map);
	void updateControllerState(DirectX::Keyboard::State device_state);
	DirectX::GamePad::State GetControllerState() const;

private:
	void SetStateValues(); 

private:
	int															input_values[DEVICE_CONTROLLER_BUTTONS_COUNT];
	std::map<DirectX::Keyboard::Keys, MetroBrawlInputActions>   input_map;
	DirectX::GamePad::State										controller_state;
};