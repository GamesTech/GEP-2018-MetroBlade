#include "pch.h"
#include "GameObject2D.h"
#include "Collider.h"


Collider::Collider(Vector2 &origin, Vector2 dimensions, bool trigger)
	:box_origin(origin),
	box_dimensions(dimensions),
	is_trigger(trigger)
{
	
}

int Collider::getTag()
{
	return m_tag;
}

void Collider::setTag(int tag)
{
	m_tag = tag;
}

float Collider::getMaxX()
{
	return max_values.x;
}

float Collider::getMaxY()
{
	return max_values.y;
}

bool Collider::getTrigger()
{
	return is_trigger;
}

Vector2 Collider::getBoxOrigin()
{
	return box_origin;
}

void Collider::setBoxOrigin(Vector2 box_origin)
{
	this->box_origin = box_origin;
}
Vector2 Collider::getMaxValues()
{
	max_values = box_origin + box_dimensions;
	return max_values;
}

