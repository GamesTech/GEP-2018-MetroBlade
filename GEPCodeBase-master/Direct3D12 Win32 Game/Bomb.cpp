#include "pch.h"
#include <functional>
#include "Bomb.h"
#include "GameStateData.h"
#include "PlayerStatus.h"
Bomb::Bomb(RenderData* _RD, string _filename, Vector2 new_direction, Player2D* original) : Physics2D(_RD, _filename)
{

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

}