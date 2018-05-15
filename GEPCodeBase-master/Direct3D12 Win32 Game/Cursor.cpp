#include "pch.h"
#include "Cursor.h"
#include "UISprite.h"
#include "RenderData.h"
#include "GameStateData.h"
#include "LobbySystem.h"

using namespace std::placeholders;
Cursor::Cursor(std::string filename, RenderData * _RD, int controller_id)
{
	sprite = new UISprite(filename, _RD);

	col->isColliderImmediate(true);
	col->addParentObjectRefrence(this);

	col->assignCollisionEvent(std::bind(&Cursor::onCollision, this, _1));
	object_components.addComponent(col);

	this->controller_id = controller_id;

	object_components.addComponent(new LobbySystemComponent);
}

Cursor::~Cursor()
{
	if (player_data.player_name != "player_null")
	{
		object_components.getComponentByType<LobbySystemComponent>()->addPlayer(player_data);
	}
}

void Cursor::CheckInput(GameStateData * _GSD)
{
	if (is_active)
	{


		float stick_x = _GSD->input->getBindRawValue("ThumbstickLeftX", controller_id);
		float stick_y = _GSD->input->getBindRawValue("ThumbstickLeftY", controller_id);


		if (_GSD->input->getBindDown("MoveRight", controller_id))
		{
			stick_x = 1;
		}
		else if (_GSD->input->getBindDown("MoveLeft", controller_id))
		{
			stick_x = -1;
		}

		if (_GSD->input->getBindDown("MoveUp", controller_id))
		{
			stick_y = 1;
		}
		else if (_GSD->input->getBindDown("MoveDown", controller_id))
		{
			stick_y = -1;
		}


		setCanvasPosition(Vector2(getCanvasPosition().x + (stick_x*speed), getCanvasPosition().y - (stick_y*speed)));

		sprite->setCanvasPosition(getCanvasPosition());

		setCanvasPosition(Vector2(getCanvasPosition().x + (stick_x*speed), getCanvasPosition().y - (stick_y*speed)));
		setCanvasPosition(Vector2(getCanvasPosition().x + (stick_x*speed), getCanvasPosition().y - (stick_y*speed)));

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

void Cursor::setPlayerData(PlayerData player_info)
{
	if (!object_components.getComponentByType<LobbySystemComponent>()->isPlayerRegistered(controller_id))
	{
		player_info.player_name = "P" + std::to_string(controller_id + 1);
		player_info.input_device_id = controller_id;
		player_data = player_info;
	}
	else
	{
		object_components.getComponentByType<LobbySystemComponent>()->getPlayerByIndex(controller_id)->character_name = player_info.character_name;
	}
}



