#include "GameObject2D.h"
#include "Collider.h"

Collider::Collider()
{

}

Collider::~Collider()
{

}

RECT Collider::getBoundingBox()
{
	RECT bounding_box;

	box_dimentions.x = xPos;
	box_dimentions.y = yPos;
	bounding_box.top = box_dimentions.y;
	bounding_box.left = box_dimentions.x;
	bounding_box.bottom = width;
	bounding_box.right = height;

	/*bounding_box.top = yPos;
	bounding_box.left = xPos;
	bounding_box.bottom = width;
	bounding_box.right = height;*/

	return bounding_box;
}