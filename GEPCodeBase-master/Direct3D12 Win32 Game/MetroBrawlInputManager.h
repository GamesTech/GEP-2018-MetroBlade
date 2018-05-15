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

#ifdef ARCADE
#include "ArcadeControllerModule.h"
#endif

class MetroBrawlInputManager 
{
public:
	MetroBrawlInputManager() = default;

	// Here we should clean up and stop controllers.
	// This way we gan garantee the controllers will stop. 
	~MetroBrawlInputManager(); 

	void init(HWND& window);
	void tick();

	// Direct Input accessors.
	bool getKeyDown(DirectX::Keyboard::Keys   key);
	bool getKeyUp(DirectX::Keyboard::Keys   key);
	bool getMouseButtonDown(MetroBrawlInputActions mouse_button);
	Vector2 getMouseCoordinates();
	int   getMouseScrollWheelValue() const;

	// Controller input accessors.
	float getControllerKeyValue(MetroBrawlInputActions  controller_button, int device_id);

	// Input Bind Accessors.
	bool getBindDown(std::string  bind);

	// per-device input checks.
	bool  getBindDown(std::string  bind, int device_id);
	float getBindRawValue(std::string bind, int device_id);

private:
	void updateControllerState();

	void loadBinds();
	void loadControllerBinds(InputBind& new_bind);

	void updateBindState();
	void updateControllerBindState();

	void getBindButtonValue(InputBind& value);

	InputBind* findBind(std::string bind);
	InputBind* findControllerBind(std::string bind);
	InputBind* findControllerBind(std::string bind, int device_id);

private:
	std::unique_ptr<DirectX::Keyboard>    keyboard_input = std::make_unique<DirectX::Keyboard>();
	std::unique_ptr<DirectX::Mouse>		  mouse_input = std::make_unique<DirectX::Mouse>();
	std::unique_ptr<DirectX::GamePad>	  gamepad_input = std::make_unique<DirectX::GamePad>();

	// Input state recorders. Allows us to retrieve input state without too much hassle.
	DirectX::Keyboard::State			  keyboard_state;
	DirectX::Mouse::State				  mouse_state;
	std::vector<ControllerStates>		  gamepad_state = std::vector<ControllerStates>(DirectX::GamePad::MAX_PLAYER_COUNT);

#ifdef ARCADE
	ArcadeControllerModule				  arcade_controls = ArcadeControllerModule(keyboard_input.get());
#else
	//std::vector<ControllerStates>		  gamepad_state = std::vector<ControllerStates>(DirectX::GamePad::MAX_PLAYER_COUNT);
#endif

private:

	// Here we need to add binds. 
	std::vector<InputBind>				  action_binds; // Keyboard and mouse binds go here.

	JSONFileReader						  input_bind_file;
};