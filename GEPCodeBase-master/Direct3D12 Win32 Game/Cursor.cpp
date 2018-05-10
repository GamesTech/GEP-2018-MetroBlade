#include "pch.h"
#include "Cursor.h"
#include "UISprite.h"
#include "RenderData.h"
#include "GameStateData.h"

using namespace std::placeholders;
Cursor::Cursor(std::string filename, RenderData * _RD, int controller_id)
{
	sprite = new UISprite(filename, _RD);

	col->isColliderImmediate(true);
	col->addParentObjectRefrence(this);

	col->assignCollisionEvent(std::bind(&Cursor::onCollision, this, _1));
	object_components.addComponent(col);

	this->controller_id = controller_id;
}

void Cursor::CheckInput(GameStateData * _GSD)
{
	controller_state = _GSD->m_gamePad->GetState(controller_id);

	float stick_x = controller_state.thumbSticks.leftX;
	float stick_y = controller_state.thumbSticks.leftY;

	setCanvasPosition(Vector2(getCanvasPosition().x + (stick_x*speed), getCanvasPosition().y - (stick_y*speed)));

	sprite->setCanvasPosition(getCanvasPosition());

	if (controller_state.IsAPressed())
	{
		a_pressed = true;
	}
	else
	{
		a_pressed = false;
	}
}

void Cursor::Tick(GameStateData * _GSD)
{
	CheckInput(_GSD);
	col->setBoxOrigin(render_position);
}

void Cursor::Render(RenderData * _RD)
{
	Vector2 viewport = _RD->m_cam->get2DViewport();
	render_position = Vector2(canvas_position.x * viewport.x, canvas_position.y * viewport.y);
	sprite->Render(_RD);
}

void Cursor::onCollision(MetroBrawlCollisionData col_data)
{
	if (a_pressed)
	{
		interact = true;
	}
	else
	{
		interact = false;
	}

	collider_tag = col_data.collider_object->getCollidersParent()->getTag();
}



