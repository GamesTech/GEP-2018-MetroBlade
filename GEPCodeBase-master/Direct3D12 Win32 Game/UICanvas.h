/**
*  @file    UICanvas.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    12/03/2018
*  @version v1.0
*
*  @section System Module
*           UI Renderer
*
*  @brief Defines the Core Object that is risponcable for rendering all UI objects.
*
*  @section Description
*	  
*	A UI Canvas defines the component that organises and sorts all UI objects. This will 
*   be risponcable for managing its own set of objects. Hence allowing UI to be superimposed
*   on the game world. 
*
*/


#pragma once

#include "pch.h"
#include "UIObject.h"

class UICanvas 
{
public:
	UICanvas() = default;
	~UICanvas() = default;

	void addUIObject(UIObject*  new_object);

private:
	std::vector<std::unique_ptr<UIObject>>	ui_objects;
	SceneState									 world;
};
