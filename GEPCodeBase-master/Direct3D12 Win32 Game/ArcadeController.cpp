#include "pch.h"
#include "ArcadeController.h"

ArcadeController::ArcadeController()
{
	// Here we setup the controller to allow it to impersonate a gamepad.
	controller_state.connected = true;
}

void ArcadeController::loadMap(std::map<DirectX::Keyboard::Keys, MetroBrawlInputActions> map)
{
	input_map = map;
}

void ArcadeController::updateControllerState(DirectX::Keyboard::State device_state)
{
	for (auto& entry : input_map) 
	{
		input_values[(entry.second - 259)] = device_state.IsKeyDown((DirectX::Keyboard::Keys)entry.first);
	}

	return;
}

DirectX::GamePad::State ArcadeController::GetControllerState() const
{
	return controller_state;
}

void ArcadeController::SetStateValues()
{
	controller_state.buttons.a = input_values[0];
	controller_state.buttons.b = input_values[1];
	controller_state.buttons.x = input_values[2];
	controller_state.buttons.y = input_values[3];
	controller_state.dpad.up = input_values[4];
	controller_state.dpad.down = input_values[5];
	controller_state.dpad.left = input_values[6];
	controller_state.dpad.right = input_values[7];
	controller_state.buttons.start = input_values[8];
	controller_state.buttons.back = input_values[9];
	controller_state.thumbSticks.leftX = input_values[10];
	controller_state.thumbSticks.leftY = input_values[11];
	controller_state.thumbSticks.rightX = input_values[12];
	controller_state.thumbSticks.rightY = input_values[13];
	controller_state.buttons.leftShoulder = input_values[14];
	controller_state.buttons.rightShoulder = input_values[15];
}
