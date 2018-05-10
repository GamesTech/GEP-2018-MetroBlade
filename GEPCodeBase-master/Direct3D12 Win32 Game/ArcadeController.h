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