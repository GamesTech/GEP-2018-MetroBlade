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
	if (is_active) 
	{
		float stick_x = _GSD->input->getBindRawValue("ThumbstickLeftX", controller_id);
		float stick_y = _GSD->input->getBindRawValue("ThumbstickLeftY", controller_id);


		setCanvasPosition(Vector2(getCanvasPosition().x + (stick_x*speed), getCanvasPosition().y - (stick_y*speed)));

		sprite->setCanvasPosition(getCanvasPosition());

		if (_GSD->input->getBindDown("Jump"))
		{
			a_pressed = true;
		}
		else
		{
			a_pressed = false;
		}
	}

	if (_GSD->input->getBindDown("Action", controller_id)) { is_active = true; }
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
	if (is_active) 
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
}



