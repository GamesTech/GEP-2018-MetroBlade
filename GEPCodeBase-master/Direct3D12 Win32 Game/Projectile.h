#pragma once
#include "ImageGO2D.h"
class Projectile : public ImageGO2D
{

public:
	Projectile(RenderData* _RD, string _filename, Vector2 new_direction);
	~Projectile();
	virtual void Tick(GameStateData* _GSD);
	bool MoveProjectile(GameStateData* _GSD);
	bool Collision();
private:
	
	const int time_max = 3;
	int current_time = time_max;
	const int damage = 25;
	bool pierce = false;
	bool isAlive = true;
	Vector2 direction = Vector2::Zero;
};