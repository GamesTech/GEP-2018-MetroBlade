#pragma once
#include "GameObject2D.h"
#include "CollisionManager.h"

class Collider
	:public CollisionManager
{
public:
	Collider();
	Collider(Vector2  origin, Vector2 dimensions, bool trigger = false);
	~Collider() = default;

	float getMaxX();
	float getMaxY();


private:
	Vector2  box_dimensions;
	Vector2  box_origin;
	Vector2  max_values;
	bool is_trigger = false;
};