/**
*  @file    Projectile.h
*  @author  Elliot Martin (GitHub - Elliotmartin97)
*  @date    14/05/2018
*  @version v1.0
*
*  @section GameObject Item Projectile
*
*
*  @brief One of the items the players can use
*
*  @section Description
*
*  A Projectile which shoots from the players position using their
*  direction and can damage other players
*/

#pragma once
#include "Physics2D.h"
#include "Sprite.h"
class Projectile : public Physics2D
{

public:
	Projectile(RenderData* _RD, string _filename, Vector2 new_direction, Player2D* original);
	~Projectile();
	virtual void Tick(GameStateData* _GSD);
	virtual void Render(RenderData* _GSD);
	void MoveProjectile(GameStateData* _GSD);
private:
	Sprite* sprite = nullptr;
	Player2D* player_original = nullptr;
	Collider* col = new Collider(Vector2(m_pos), Vector2(100, 130), false);
	const float time_max = 3.0f;
	float current_time = time_max;
	const int damage = 25;
	bool pierce = false;
	bool alive = true;
	float x_speed = 300.0f;
	Vector2 direction = Vector2::Zero;
	float y_offset = 50.0f;
	void onCollision(MetroBrawlCollisionData  col_data);
	float damage_amount = 25.0f;

}; 
