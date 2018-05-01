#pragma once
#include "GameObject2D.h"
#include "GameComponent.h"

class Collider
{
public:
	Collider() = default;
	Collider(Vector2  &origin, Vector2 dimensions, bool trigger = false);
	~Collider() = default;

	int getTag();
	void setTag(int tag);

	float getMaxX();
	float getMaxY();
	bool getTrigger();

	Vector2 getBoxOrigin();
	void setBoxOrigin(Vector2 box_origin);
	Vector2 getMaxValues();

	void isColliderActive(bool is_active);
	bool iscolliderActive() const;

	void isColliderImmediate(bool is_immediate);
	bool isColliderImmediate() const;

private:
	int m_tag;
	Vector2  box_dimensions;
	Vector2  box_origin;
	Vector2  max_values;
	bool is_trigger = false;

	bool is_collider_immediate = false;
	bool is_collider_active = true;
};