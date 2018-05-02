#include "pch.h"
#include "Projectile.h"
#include "GameStateData.h"
Projectile::Projectile(RenderData* _RD, string _filename, Vector2 new_direction) : ImageGO2D(_RD, _filename)
{
	direction = new_direction;
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
		if (!MoveProjectile(_GSD))
		{
			isAlive = false;
		}
	}

	if (isAlive == false)
	{
		//destroy self
	}
}

bool Projectile::MoveProjectile(GameStateData* _GSD)
{
	if (!Collision())
	{

	}
	else
	{
		//apply damage to collider
		return false;
	}
}

bool Projectile::Collision()
{
	//check if colliding with anything
	//if colliding check if pierce is true
	return false;
}