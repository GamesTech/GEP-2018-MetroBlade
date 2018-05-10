#include "pch.h"
#include <functional>
#include "Bomb.h"
#include "GameStateData.h"
#include "PlayerStatus.h"
Bomb::Bomb(RenderData* _RD, string _filename, Vector2 new_direction, Player2D* original) : Physics2D(_RD, _filename)
{
	using namespace std::placeholders;

	Vector2 new_pos = original->GetPos();
	SetPos(new_pos);

	col->isColliderImmediate(true);
	col->setBoxDimensions(Vector2(100, 100));
	col->addParentObjectRefrence(this);
	col->assignCollisionEvent(std::bind(&Bomb::onCollision, this, _1));
	object_components.addComponent(col);

	src_rect.reset(new RECT);
	object_components.addComponent(new Sprite(true));
	sprite = object_components.getComponentByType<Sprite>();
	sprite->setSpriteRECT(src_rect);
	sprite->setSpriteAnimationFile(_filename + "_animations");
	sprite->setAnimationState("tick");
}

Bomb::~Bomb()
{
}

void Bomb::Tick(GameStateData* _GSD)
{
	current_time -= _GSD->m_dt;

	if (current_time <= 0.0f)
	{
		explode(_GSD);
	}

	sprite->tickComponent(_GSD);
	Physics2D::Tick(_GSD);
}

void Bomb::Render(RenderData* _RD)
{
	ImageGO2D::Render(_RD);
}

void Bomb::explode(GameStateData* _GSD)
{
	//set collider active
}

void Bomb::onCollision(MetroBrawlCollisionData  col_data)
{
	Player2D*   player = dynamic_cast<Player2D*>(col_data.collider_object->getCollidersParent());
	if (player)
	{

	}
}