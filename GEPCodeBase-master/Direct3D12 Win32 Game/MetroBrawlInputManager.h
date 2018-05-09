/**
*  @file    MetroBrawlInputManager.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    08/05/2018
*  @version v1.0
*
*  @section System Module
*           Input
*
*  @brief Definition for Audio Manager System.
*
*  @section Description
*  Defines the Input subsystem which allows all input to be captured and then 
*  
*/


#pragma once

#include "pch.h"
#include "JSONFileReader.h"

#include "InputBind.h"

class MetroBrawlInputManager 
{
public:
	MetroBrawlInputManager() = default;

	// Here we should clean up and stop controllers.
	// This way we gan garantee the controllers will stop. 
	~MetroBrawlInputManager() = default; 

	void init(HWND& window);
	void tick();

	// Direct Input accessors.
	bool getKeyDown(DirectX::Keyboard::Keys   key);
	bool getKeyUp(DirectX::Keyboard::Keys   key);
	bool getMouseButtonDown();
	Vector2 getMouseCoordinates();
	int   getMouseScrollWheelValue() const;

	// Input Bind Accessors. 
	bool getBindDown(std::string  bind);

private:
	// per frame update routienes
	void loadBinds();
	void updateBindState();

	InputBind*	findBind(std::string bind);

private:
	std::unique_ptr<DirectX::Keyboard>    keyboard_input = std::make_unique<DirectX::Keyboard>();
	std::unique_ptr<DirectX::Mouse>		  mouse_input = std::make_unique<DirectX::Mouse>();
	std::unique_ptr<DirectX::GamePad>	  gamepad_input = std::make_unique<DirectX::GamePad>();

	// Input state recorders. Allows us to retrieve input state without too much hassle.
	DirectX::Keyboard::State			  keyboard_state;
	DirectX::Mouse::State				  mouse_state;
	std::vector<DirectX::GamePad::State>  gamepad_state = std::vector<DirectX::GamePad::State>(DirectX::GamePad::MAX_PLAYER_COUNT);

private:
	// Here we need to add binds. 
	std::vector<InputBind>				  action_binds;
	JSONFileReader						  input_bind_file;
};