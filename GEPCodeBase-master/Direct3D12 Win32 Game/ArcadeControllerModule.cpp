#include "pch.h"
#include "ArcadeControllerModule.h"

ArcadeControllerModule::ArcadeControllerModule(DirectX::Keyboard* keyboard_refrence)
	: keyboard(keyboard_refrence)
{
}

void ArcadeControllerModule::initModule(std::string bind_file)
{
	// Here we will parse the maps in manually
	// TODO - Add a system where files are loaded in for bindings instead.

	// All bindings for the arcade machiene go here.
	// They are loaded into the corrisponding controllers when this driver is initialised. 
	std::map<DirectX::Keyboard::Keys, MetroBrawlInputActions>   key_map;
	key_map.emplace(DirectX::Keyboard::Keys::LeftShift, MetroBrawlInputActions::KEY_CONTROLLER_A);
	key_map.emplace(DirectX::Keyboard::Keys::Z, MetroBrawlInputActions::KEY_CONTROLLER_B);
	key_map.emplace(DirectX::Keyboard::Keys::LeftControl, MetroBrawlInputActions::KEY_CONTROLLER_X);
	key_map.emplace(DirectX::Keyboard::Keys::LeftAlt, MetroBrawlInputActions::KEY_CONTROLLER_Y);
	key_map.emplace(DirectX::Keyboard::Keys::LeftAlt, MetroBrawlInputActions::KEY_CONTROLLER_Y);
	key_map.emplace(DirectX::Keyboard::Keys::Up, MetroBrawlInputActions::KEY_CONTROLLER_DPAD_UP);
	key_map.emplace(DirectX::Keyboard::Keys::Down, MetroBrawlInputActions::KEY_CONTROLLER_DPAD_DOWN);
	key_map.emplace(DirectX::Keyboard::Keys::Left, MetroBrawlInputActions::KEY_CONTROLLER_DPAD_LEFT);
	key_map.emplace(DirectX::Keyboard::Keys::Right, MetroBrawlInputActions::KEY_CONTROLLER_DPAD_RIGHT);
	key_map.emplace(DirectX::Keyboard::Keys::D1, MetroBrawlInputActions::KEY_CONTROLLER_START);
	key_map.emplace(DirectX::Keyboard::Keys::Space, MetroBrawlInputActions::KEY_CONTROLLER_BACK);
	controllers[0].loadMap(key_map);

	key_map.clear();

	key_map.emplace(DirectX::Keyboard::Keys::W, MetroBrawlInputActions::KEY_CONTROLLER_A);
	key_map.emplace(DirectX::Keyboard::Keys::I, MetroBrawlInputActions::KEY_CONTROLLER_B);
	key_map.emplace(DirectX::Keyboard::Keys::A, MetroBrawlInputActions::KEY_CONTROLLER_X);
	key_map.emplace(DirectX::Keyboard::Keys::S, MetroBrawlInputActions::KEY_CONTROLLER_Y);
	key_map.emplace(DirectX::Keyboard::Keys::R, MetroBrawlInputActions::KEY_CONTROLLER_DPAD_UP);
	key_map.emplace(DirectX::Keyboard::Keys::F, MetroBrawlInputActions::KEY_CONTROLLER_DPAD_DOWN);
	key_map.emplace(DirectX::Keyboard::Keys::D, MetroBrawlInputActions::KEY_CONTROLLER_DPAD_LEFT);
	key_map.emplace(DirectX::Keyboard::Keys::G, MetroBrawlInputActions::KEY_CONTROLLER_DPAD_RIGHT);
	key_map.emplace(DirectX::Keyboard::Keys::D2, MetroBrawlInputActions::KEY_CONTROLLER_START);
	key_map.emplace(DirectX::Keyboard::Keys::Q, MetroBrawlInputActions::KEY_CONTROLLER_BACK);
	controllers[1].loadMap(key_map);

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
