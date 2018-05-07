#include "pch.h"
#include <functional>
#include "Projectile.h"
#include "GameStateData.h"
#include "PlayerStatus.h"
Projectile::Projectile(RenderData* _RD, string _filename, Vector2 new_direction, Player2D* original) : Physics2D(_RD, _filename)
{
	using namespace std::placeholders;

	direction = new_direction;
	player_original = original;

	col->addParentObjectRefrence(this);
	col->assignCollisionEvent(std::bind(&Projectile::onCollision, this, _1));
	object_components.addComponent(col);
}

Projectile::~Projectile()
{
}

void Projectile::Tick(GameStateData* _GSD)
{
	current_time -= _GSD->m_dt;
	
	if (current_time <= 0)
	{
		isAlive = false;
	}
	else
	{
		MoveProjectile(_GSD);
	}

	Physics2D::Tick(_GSD);
}

void Projectile::MoveProjectile(GameStateData* _GSD)
{
	Vector2 new_speed = direction;
	new_speed.x *= x_speed;
	SetInputVel(new_speed);
}

void Projectile::onCollision(MetroBrawlCollisionData  col_data)
{
	Player2D*   player = dynamic_cast<Player2D*>(col_data.collider_object->getCollidersParent());
	if (player)
	{
		if (player == player_original)
		{
			//ignore
		}
		else
		{
			player->getComponentManager()->getComponentByType<PlayerStatus>()->takeHealth(damage_amount);

		}
	}
}