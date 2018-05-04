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
#include "InputManager.h"
class UISprite;

class Cursor : public UIObject
{

public:
	Cursor(std::string filename, RenderData* _RD);
	~Cursor() = default;

	void CheckInput(GameStateData* _GSD);
private:
	UISprite * sprite = nullptr;
	int controller_id = 0;
	float speed = 2.0f;

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;
};