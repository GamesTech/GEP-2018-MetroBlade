#include "InputManager.h"

void InputManager::init()
{
	m_gamePad = std::make_unique<DirectX::GamePad>();
}
void InputManager::LoadInputSettings()
{
	// Load file here.
}

void InputManager::UpdateInput()
{
	DirectX::Keyboard::State key_state;
	//Gamepad state and gamepad button state tracker have different methods, there is no iskeydown for gamepad
	//DirectX::GamePad::State controller_state;
	DirectX::GamePad::ButtonStateTracker controller_state;
	key_state = m_keyboard->GetState();
	//getstate() needs a number for the player

	//controller_state = m_gamePad->GetState(0);

	//keyboard
	for (int i = 0; i < input_data_list.size(); i++) 
	{
		input_data_list[i].pressed = key_state.IsKeyDown(input_data_list[i].keys);
	}
	//gamepad
	for (int i = 0; i < input_data_list.size(); i++)
	{
		//input_data_list[i].pressed = controller_state.
	}
}