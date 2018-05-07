#pragma once
#include "Physics2D.h"
class Projectile : public Physics2D
{

public:
	Projectile(RenderData* _RD, string _filename, Vector2 new_direction, Player2D* original);
	~Projectile();
	virtual void Tick(GameStateData* _GSD);
	void MoveProjectile(GameStateData* _GSD);
	bool Collision();
private:
	Player2D* player_original = nullptr;
	Collider* col = new Collider(Vector2(m_pos), Vector2(100, 130), false);
	const int time_max = 3;
	int current_time = time_max;
	const int damage = 25;
	bool pierce = false;
	bool isAlive = true;
	float x_speed = 100.0f;
	Vector2 direction = Vector2::Zero;
	void onCollision(MetroBrawlCollisionData  col_data);
	float damage_amount = 25.0f;
}; 
