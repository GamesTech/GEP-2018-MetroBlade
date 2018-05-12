#pragma once
#include "pch.h"

//GEP:: Basic data of current GameState to communicate to all Game Objects

struct GameStateData
{
	Keyboard::State m_keyboardState;
	Keyboard::State m_prevKeyboardState;
	Mouse::State m_mouseState;
	std::unique_ptr<DirectX::GamePad> m_gamePad = std::make_unique<DirectX::GamePad>();
	//length of time since last frame
	float m_dt;
};
