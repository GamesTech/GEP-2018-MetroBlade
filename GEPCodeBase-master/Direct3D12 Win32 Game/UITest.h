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

#include "UIObject.h"

class UITest : public UIObject 
{
public: 
	UITest(RenderData*  _RD);
	~UITest() = default;

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;

private:
	std::unique_ptr<ImageGO2D>    testImage;
};