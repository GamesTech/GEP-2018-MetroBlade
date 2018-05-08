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

enum class INPUT_BUTTONS : int
{
	BUTTON_LEFT,
	BUTTON_MIDDLE,
	BUTTON_RIGHT
};


class MetroBrawlInputManager 
{
public:
	MetroBrawlInputManager() = default;
	~MetroBrawlInputManager() = default;

	void init(HWND& window);
	void tick();

	// Direct Input accessors.
	bool getKeyDown(DirectX::Keyboard::Keys   key);
	bool getKeyUp(DirectX::Keyboard::Keys   key);
	bool getMouseButtonDown();
	Vector2 getMouseCoordinates();
	int   getMouseScrollWheelValue() const;

	// Bound Input Accessors. 


private:
	std::unique_ptr<DirectX::Keyboard>    keyboard_input = std::make_unique<DirectX::Keyboard>();
	std::unique_ptr<DirectX::Mouse>		  mouse_input = std::make_unique<DirectX::Mouse>();

	// TODO - Consider Removing.
	DirectX::Keyboard::State			  keyboard_state;
	DirectX::Mouse::State				  mouse_state;

private:
	// Here we need to add binds. 

};