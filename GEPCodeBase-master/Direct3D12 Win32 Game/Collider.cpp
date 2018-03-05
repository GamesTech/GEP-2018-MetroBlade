#include "GameObject2D.h"
#include "Collider.h"



Collider::Collider()
{
}

Collider::Collider(Vector2 origin, Vector2 dimensions, bool trigger)
	:box_origin(origin),
	box_dimensions(dimensions),
	is_trigger(trigger)
{
	max_values = box_origin + box_dimensions;
}

float Collider::getMaxX()
{
	return max_values.x;
}

float Collider::getMaxY()
{
	return max_values.y;
}
