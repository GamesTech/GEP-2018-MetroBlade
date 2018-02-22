#include "GameObject2D.h"
#include "Collider.h"

Collider::Collider()
{

}

Collider::~Collider()
{

}

Vector2 Collider::getBoundingBox(RECT& collision_box)
{
	Vector2 bounding_box;

	bounding_box.x = xPos;
	bounding_box.y = yPos;
	collision_box.top = bounding_box.y;
	collision_box.left = bounding_box.x;
	collision_box.bottom = width;
	collision_box.right = height;

	/*bounding_box.top = yPos;
	bounding_box.left = xPos;
	bounding_box.bottom = width;
	bounding_box.right = height;*/

	return bounding_box;
}