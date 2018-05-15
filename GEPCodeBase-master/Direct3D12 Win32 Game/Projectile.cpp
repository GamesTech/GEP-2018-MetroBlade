#include "pch.h"
#include <functional>
#include "Projectile.h"
#include "GameStateData.h"
#include "PlayerStatus.h"
Projectile::Projectile(RenderData* _RD, string _filename) : Physics2D(_RD, _filename)
{
	using namespace std::placeholders;


	col->isColliderImmediate(true);
	col->setBoxDimensions(Vector2(50, 50));
	col->addParentObjectRefrence(this);
	col->assignCollisionEvent(std::bind(&Projectile::onCollision, this, _1));
	object_components.addComponent(col);

	src_rect.reset(new RECT);
	object_components.addComponent(new Sprite(true));
	sprite = object_components.getComponentByType<Sprite>();
	sprite->setSpriteRECT(src_rect);
	sprite->setSpriteAnimationFile(_filename + "_animations");
	sprite->setAnimationState("move");
}

Projectile::~Projectile()
{
}

void Projectile::StartProjectile(Player2D* player)
{
	Vector2 new_pos = player->GetPos();
	new_pos.y -= y_offset;
	SetPos(new_pos);
	player_original = player;
	direction = player->getDirection();
	alive = true;
}

void Projectile::Tick(GameStateData* _GSD)
{

	if(alive)
	{ 
		current_time -= _GSD->m_dt;

		if (current_time <= 0.0f || hit_player)
		{
			sprite->setLoop(false);
			sprite->setAnimationState("hit");
			col->isColliderActive(false);
			alive = false;
		}
		else
		{
			MoveProjectile(_GSD);
		}
		col->setBoxOrigin(m_pos);
		sprite->tickComponent(_GSD);
		Physics2D::Tick(_GSD);
	}
	else
	{
		current_time = time_max;
		SetPos(Vector2(-100, -100));
		sprite->setAnimationState("move");
		sprite->setLoop(true);
		hit_player = false;
	}
	

}

void Projectile::Render(RenderData* _GSD)
{
	if (alive)
	{
		ImageGO2D::Render(_GSD);
	}
}

void Projectile::MoveProjectile(GameStateData* _GSD)
{
	Vector2 new_speed = direction;
	new_speed.x = x_speed * _GSD->m_dt;
	SetInputVel(new_speed);
}

void Projectile::onCollision(MetroBrawlCollisionData  col_data)
{
	if (alive)
	{
		Player2D*   player = dynamic_cast<Player2D*>(col_data.collider_object->getCollidersParent());
		if (player)
		{
			if (player != player_original)
			{
				player->getComponentManager()->getComponentByType<PlayerStatus>()->takeHealth(damage_amount);
				hit_player = true;
			}

		}
	}
}