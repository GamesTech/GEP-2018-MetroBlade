#pragma once
#include "GameObject2D.h"

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

private:
	int m_tag;
	Vector2  box_dimensions;
	Vector2  box_origin;
	Vector2  max_values;
	bool is_trigger = false;
};