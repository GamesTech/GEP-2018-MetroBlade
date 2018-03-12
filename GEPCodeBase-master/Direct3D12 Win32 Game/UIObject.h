/**
*  @file    UICanvas.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    12/03/2018
*  @version v1.0
*
*  @section System Module
*           UI Renderer
*
*  @brief Defines a UI object.
*
*  @section Description
*
*	A UI Object is any object that is managed by the UICanvas and is being used to display information on screen.
*   It takes the form of a modified game object. 
*
*/


#pragma once

#include "pch.h"
#include "GameObject2D.h"

class UIObject : public GameObject2D 
{
public: 
	UIObject() = default;
	~UIObject() = default; 

	// Inherited via GameObject2D
	virtual void CentreOrigin() override;

	virtual void Tick(GameStateData * _GSD) override;

	virtual void Render(RenderData * _RD) override;

private:
	Vector2		canvas_position; //< The Normalised position of the UI Element on the canvas. Scales with resolution. 
};