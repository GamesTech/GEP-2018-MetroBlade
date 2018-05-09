#include "pch.h"
#include <functional>
#include "Hammer.h"
#include "GameStateData.h"
#include "PlayerStatus.h"
Hammer::Hammer(RenderData* _RD, string _filename, Vector2 new_direction, Player2D* original) : Physics2D(_RD, _filename)
{
	using namespace std::placeholders;

	player_original = original;

	col->isColliderImmediate(true);
	col->setBoxDimensions(Vector2(50, 50));
	col->addParentObjectRefrence(this);
	col->assignCollisionEvent(std::bind(&Hammer::onCollision, this, _1));
	object_components.addComponent(col);

	src_rect.reset(new RECT);
	object_components.addComponent(new Sprite(true));
	sprite = object_components.getComponentByType<Sprite>();
	sprite->setSpriteRECT(src_rect);
	sprite->setSpriteAnimationFile(_filename + "_animations");
	sprite->setLoop(false);
	sprite->setAnimationState("attack");
	
}

Hammer::~Hammer()
{
}

void Hammer::Tick(GameStateData* _GSD)
{
	m_pos = player_original->GetPos();
	current_time -= _GSD->m_dt;
	if (current_time <= 0.0f || !alive)
	{
		//end
	}
	else
	{
		attack(_GSD);
	}
	m_pos = player_original->GetPos();
	col->setBoxOrigin(m_pos);
	sprite->tickComponent(_GSD);
	Physics2D::Tick(_GSD);
}

void Hammer::Render(RenderData* _RD)
{
	ImageGO2D::Render(_RD);
}

void Hammer::attack(GameStateData* _GSD)
{
	col_offset = col->getBoxOrigin();
	col_offset.y += current_hammer_height;
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