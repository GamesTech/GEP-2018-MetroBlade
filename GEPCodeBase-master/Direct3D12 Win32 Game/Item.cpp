#include "pch.h"
#include <functional>
#include "PlayerStatus.h"
#include "Item.h"
#include "Projectile.h"
#include "Hammer.h"
#include "Bomb.h"
#include "GameStateData.h"

Item::Item(RenderData* _RD, string _filename, Vector2 position, int item_num) : Physics2D(_RD, _filename)
{
	using namespace std::placeholders;


	item_pos = position;
	SetPos(position);
	CentreOrigin();
	
	col->addParentObjectRefrence(this);
	col->assignCollisionEvent(std::bind(&Item::onCollision, this, _1));
	object_components.addComponent(col);

	item_type = (ItemType)item_num;

	src_rect.reset(new RECT);
	object_components.addComponent(new Sprite(true));
	sprite = object_components.getComponentByType<Sprite>();
	sprite->setSpriteRECT(src_rect);
	sprite->setSpriteAnimationFile(_filename + "_animations");
	
	switch (item_type)
	{
	case HEALTH:
		sprite->setAnimationState("health");
		break;
	case PROJECTILE:
		sprite->setAnimationState("projectile");
		break;
	case HAMMER:
		sprite->setAnimationState("hammer");
		break;
	case BOMB:
		sprite->setAnimationState("bomb");
		break;
	}

	
}

Item::~Item()
{
}

void Item::SetPosition(Vector2 new_pos)
{
	pos = new_pos;
}

void Item::Tick(GameStateData* _GSD)
{
	col->setBoxOrigin(m_pos);
	sprite->tickComponent(_GSD);
	m_acc += (gravity * Vector2::UnitY);

	if (respawning)
	{
		if (respawn_time >= 0.0f)
		{
			respawn_time -= _GSD->m_dt;
		}
		else
		{
			SetPos(item_pos);
			item_state = PICKUP;
			col->isColliderActive(true);
			respawn_time = max_time;
			m_acc = Vector2::Zero;
			respawning = false;
		}
	}
	Physics2D::Tick(_GSD);
}

void Item::Render(RenderData * _GSD)
{
	if (item_state != NONE)
	{
		ImageGO2D::Render(_GSD);
	}
}

void Item::UseItem(RenderData* _RD, Player2D* player, ItemType type)
{
	switch (type)
	{
	case HEALTH:
		player->getComponentManager()->getComponentByType<PlayerStatus>()->addHealth(health_amount);
		break;
	case PROJECTILE:
		if (proj)
		{
			proj->StartProjectile(player);
		}
		else
		{
			proj = new Projectile(_RD, "projectile_item");
			world.instantiateToScene(proj);
			proj->StartProjectile(player);
		}
		break;
	case HAMMER:
		if (ham)
		{
			
		}
		else
		{
			ham = new Hammer(_RD, "hammer_item", player->getDirection(),player);
			world.instantiateToScene(ham);
		}
		break;
	case BOMB:
		if (bomb)
		{

		}
		else
		{
			bomb = new Bomb(_RD, "bomb_item", player->getDirection(), player);
			world.instantiateToScene(bomb);
		}
		break;
	}
	respawning = true;
}


void Item::onCollision(MetroBrawlCollisionData  col_data)
{
	if (item_state == PICKUP)
	{
		Player2D*   player = dynamic_cast<Player2D*>(col_data.collider_object->getCollidersParent());
		if (player && player->hasItem() == false)
		{
			player->AddItem(this, 1);
			item_state = NONE;
			col->isColliderActive(false);
		}
	}
}