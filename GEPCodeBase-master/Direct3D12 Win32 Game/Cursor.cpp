#include "pch.h"
#include "Cursor.h"
#include "UISprite.h"
#include "RenderData.h"
#include "GameStateData.h"

using namespace std::placeholders;
Cursor::Cursor(std::string filename, RenderData * _RD)
{
	sprite = new UISprite(filename, _RD);

	col->isColliderImmediate(true);
	col->addParentObjectRefrence(this);

	col->assignCollisionEvent(std::bind(&Cursor::onCollision, this, _1));
	object_components.addComponent(col);
}

void Cursor::CheckInput(GameStateData * _GSD)
{
	controller_state = _GSD->m_gamePad->GetState(controller_id);

	float stick_x = controller_state.thumbSticks.leftX;
	float stick_y = controller_state.thumbSticks.leftY;

	SetPos(Vector2(GetPos().x + (stick_x*speed), GetPos().y - (stick_y*speed)));

	sprite->SetPos(GetPos());

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
	col->setBoxOrigin(m_pos);
}

void Cursor::Render(RenderData * _RD)
{
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
}

