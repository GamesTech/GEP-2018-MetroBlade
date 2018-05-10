#include "pch.h"
#include "ArcadeControllerModule.h"

ArcadeControllerModule::ArcadeControllerModule(DirectX::Keyboard* keyboard_refrence)
	: keyboard(keyboard_refrence)
{

}

void ArcadeControllerModule::initModule(std::string bind_file)
{
	// Here we will parse the maps in manually
	std::map<DirectX::Keyboard::Keys, MetroBrawlInputActions>   key_map;
	key_map.emplace(DirectX::Keyboard::Keys::LeftShift, MetroBrawlInputActions::KEY_CONTROLLER_A);
	key_map.emplace(DirectX::Keyboard::Keys::Z, MetroBrawlInputActions::KEY_CONTROLLER_B);
	key_map.emplace(DirectX::Keyboard::Keys::LeftControl, MetroBrawlInputActions::KEY_CONTROLLER_X);
	key_map.emplace(DirectX::Keyboard::Keys::LeftAlt, MetroBrawlInputActions::KEY_CONTROLLER_Y);
	controllers[0].loadMap(key_map);

}

void ArcadeControllerModule::tickDriver()
{
	for (auto& controller : controllers) 
	{
		controller.updateControllerState(keyboard->GetState());
	}
}

DirectX::GamePad::State ArcadeControllerModule::getControllerState(int index)
{
	return controllers[index].GetControllerState();
}
