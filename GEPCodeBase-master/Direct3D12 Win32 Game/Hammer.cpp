#include "pch.h"
#include <functional>
#include "Hammer.h"
#include "GameStateData.h"
#include "PlayerStatus.h"
Hammer::Hammer(RenderData* _RD, string _filename, Vector2 new_direction, Player2D* original) : Physics2D(_RD, _filename)
{
	using namespace std::placeholders;

	player_original = original;
	pos_offset = original->GetPos() - original->getComponentManager()->getComponentByType<Collider>()->getBoxDimenstions();
	SetPos(pos_offset);
	col->isColliderImmediate(true);
	col->setBoxDimensions(Vector2(50, 50));
	col->addParentObjectRefrence(this);
	col->assignCollisionEvent(std::bind(&Hammer::onCollision, this, _1));
	object_components.addComponent(col);
	col->isColliderActive(false);

	src_rect.reset(new RECT);
	object_components.addComponent(new Sprite(true));
	sprite = object_components.getComponentByType<Sprite>();
	sprite->setSpriteRECT(src_rect);
	sprite->setSpriteAnimationFile(_filename + "_animations");
}

Hammer::~Hammer()
{
}

void Hammer::Tick(GameStateData* _GSD)
{
	current_time -= _GSD->m_dt;

	if (current_time <= 1.5f)
	{
		col->isColliderActive(true);
	}
	if (current_time <= 0.0f)
	{
		//end
	}
	else
	{
		attack(_GSD);
	}

	sprite->tickComponent(_GSD);
	Physics2D::Tick(_GSD);
}

void Hammer::Render(RenderData* _RD)
{
	ImageGO2D::Render(_RD);
}

void Hammer::attack(GameStateData* _GSD)
{
	sprite->setLoop(false);
	sprite->setAnimationState("attack");
	col->isColliderActive(true);
}

void Hammer::onCollision(MetroBrawlCollisionData  col_data)
{
	Player2D*   player = dynamic_cast<Player2D*>(col_data.collider_object->getCollidersParent());
	if (player)
	{
		if (player != player_original)
		{
			player->getComponentManager()->getComponentByType<PlayerStatus>()->takeHealth(damage_amount);
			alive = false;
		}
		
	}
}