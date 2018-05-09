/**
*  @file    Cursor.h
*  @author  Jack Watson (GitHub - JackW8335)
*  @date    09/05/2018
*  @version v1.0
*
*  @section System Module
*           Cursor UI
*
*  @brief Defines a Cursor Object.
*
*  @section Description
*
*	Utilises the built in functionality of UI Object with inheritance, and composition for UISprite.
*   As the sprite is rendered directly inside Cursor the object can be instanciated rather than the sprite itself.
*   The thumb stick axis provide multipliers for direction and speed is for the amount the cursor moves.
* e.g. m_pos += stickAxis * speed
*/
#pragma once

#include "GameObject2D.h"
#include "UISprite.h"
#include "Cursor.h"

class TeamSelect : public GameObject2D
{
public:
	TeamSelect() = default;
	~TeamSelect() = default;
	void update(std::vector<Cursor*> cursors, std::vector<UISprite*> teamview, std::vector<std::string> teamview_images);
};