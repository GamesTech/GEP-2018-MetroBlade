/**
*  @file    ArcadeControllerModule.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    10/05/2018
*  @version v1.0
*
*  @section System Module
*           Input/Arcade
*
*  @brief Definition for An Arcade Controller.
*
*  @section Description
*  An arcade controller is in essence represented by a keyboard. 
*  This class defines an object which will return a Controller state.
*  Allows already existant key bindings to be used
*/


#pragma once

#include "pch.h"

class ArcadeControllerModule 
{
public:
	ArcadeControllerModule(DirectX::Keyboard*  keyboard_refrence);

	void initModule(); // Load the game controllers here and then update

	void tickDriver(); // Updates controller state. 

private:
	DirectX::Keyboard*  keyboard;
};