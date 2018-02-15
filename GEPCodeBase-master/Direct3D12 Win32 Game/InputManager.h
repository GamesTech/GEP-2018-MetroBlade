#pragma once

#include "Keyboard.h"
#include "GamePad.h"
#include <vector>

struct InputData {

	std::string binding;
	DirectX::Keyboard::Keys	keys;
	bool pressed;
};


class InputManager
{
public:
	InputManager() = default;
	~InputManager();
	void init();
	void LoadInputSettings();
	void UpdateInput();

private:

	std::vector<InputData> input_data_list;
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::GamePad> m_gamePad;
	
 };