/**
*  @file    Cursor.h
*  @author  Jack Watson (GitHub - JackW8335)
*  @date    04/05/2018
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
#include "UIObject.h"
#include "InputManager.h"
class UISprite;

class Cursor : public UIObject
{

public:
	Cursor(std::string filename, RenderData* _RD);
	~Cursor() = default;

	void CheckInput(GameStateData* _GSD);
	void onCollision(MetroBrawlCollisionData  col_data);

	bool getInteract(){ return interact; }

private:
	DirectX::GamePad::State controller_state;
	UISprite * sprite = nullptr;
	int controller_id = 0;
	float speed = 2.0f;

	bool interact = false;
	bool a_pressed = false;

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;

	Collider* col = new Collider(Vector2(m_pos), Vector2(40, 40), true);
	
};