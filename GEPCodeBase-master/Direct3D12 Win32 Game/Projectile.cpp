#include "pch.h"
#include <functional>
#include "Projectile.h"
#include "GameStateData.h"
#include "PlayerStatus.h"
Projectile::Projectile(RenderData* _RD, string _filename, Vector2 new_direction, Player2D* original) : Physics2D(_RD, _filename)
{
	using namespace std::placeholders;

	direction = new_direction;

	Vector2 new_pos = original->GetPos();
	new_pos.y -= y_offset;
	SetPos(new_pos);

	player_original = original;

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

void Projectile::Tick(GameStateData* _GSD)
{
	current_time -= _GSD->m_dt;
	
	if (current_time <= 0.0f || !alive)
	{
		sprite->setLoop(false);
		sprite->setAnimationState("hit");
	}
	else
	{
		MoveProjectile(_GSD);
	}
	col->setBoxOrigin(m_pos);
	sprite->tickComponent(_GSD);
	Physics2D::Tick(_GSD);

}

void Projectile::Render(RenderData* _GSD)
{
	ImageGO2D::Render(_GSD);
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
			alive = false;
		}
	}
}