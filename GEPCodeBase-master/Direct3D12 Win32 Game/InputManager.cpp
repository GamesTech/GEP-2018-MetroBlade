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
	DirectX::Keyboard::State     keyState;
	keyState = m_keyboard->GetState();
	for (int i = 0; i < input_data_list.size(); i++) 
	{
		input_data_list[i].pressed = keyState.IsKeyDown(input_data_list[i].keys);
	}
}