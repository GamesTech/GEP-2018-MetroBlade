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

void Collider::isColliderActive(bool is_active)
{
	is_collider_active = is_active;
}

bool Collider::isColliderActive() const
{
	return is_collider_active;
}

void Collider::isColliderImmediate(bool is_immediate)
{
	is_collider_immediate = is_immediate;
}

bool Collider::isColliderImmediate() const
{
	return is_collider_immediate;
}

void Collider::addParentObjectRefrence(GameObject2D * gameobject)
{
	parent_object = gameobject;
}

void Collider::assignCollisionEvent(std::function<void(MetroBrawlCollisionData)> func_delegate)
{
	collision_event_deligate = func_delegate;
}

void Collider::OnCollision(MetroBrawlCollisionData col_data)
{
	if (collision_event_deligate) 
	{
		collision_event_deligate(col_data);
	}
}

GameObject2D* Collider::getCollidersParent()
{
	return  parent_object;
}

void Collider::tickComponent(GameStateData * _GSD)
{
	return;
}

void Collider::renderComponent(RenderData * _RD)
{
	return;
}

