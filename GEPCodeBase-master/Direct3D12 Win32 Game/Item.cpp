#include "pch.h"
#include <functional>
#include "PlayerStatus.h"
#include "Item.h"
#include "Projectile.h"
#include "Hammer.h"
#include "Bomb.h"

Item::Item(RenderData* _RD, string _filename, ItemType type) : ImageGO2D(_RD, _filename)
{
	using namespace std::placeholders;
	item_type = type;
	CentreOrigin();
	col->addParentObjectRefrence(this);
	col->assignCollisionEvent(std::bind(&Item::onCollision, this, _1));
	object_components.addComponent(col);

	src_rect.reset(new RECT);
	object_components.addComponent(new Sprite(true));
	sprite = object_components.getComponentByType<Sprite>();
	sprite->setSpriteRECT(src_rect);
	sprite->setSpriteAnimationFile(_filename + "_animations");
	
	switch (type)
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
		proj = new Projectile(_RD, "projectile_item", player->getDirection(), player);
		world.instantiateToScene(proj);
		break;
	case HAMMER:
		ham = new Hammer(_RD, "hammer_item", player->getDirection(), player);
		world.instantiateToScene(ham);
		break;
	case BOMB:
		bomb = new Bomb(_RD, "bomb_item", player->getDirection(), player);
		world.instantiateToScene(bomb);
		break;
	}

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
			sprite->setLoop(false);
		}
	}
}