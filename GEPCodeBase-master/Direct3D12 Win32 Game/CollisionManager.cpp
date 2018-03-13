#include "pch.h"
#include "CollisionManager.h"


void CollisionManager::init()
{
	colliders.reserve(20);
}
void CollisionManager::addCollider(Collider collider)
{
	colliders.push_back(collider);
}

bool CollisionManager::boundingBox(Vector2 wallType, int rect2ID)
{
	if (wallType.x <= colliders[rect2ID].getMaxValues().x &&
		wallType.x >= colliders[rect2ID].getBoxOrigin().x &&
		wallType.y <= colliders[rect2ID].getMaxValues().y &&
		wallType.y >= colliders[rect2ID].getBoxOrigin().y)
	{
		return true;
	}
	return false;
}

bool CollisionManager::checkCollisions(int id)
{
	if (!colliders.empty())
	{
		for (int i = 0; i < colliders.size(); i++)
		{
			if (id != i)
			{
				updateBoundingBox(id);
				if (boundingBox(left, i))
				{
					return true;
				}
				else if (boundingBox(right, i))
				{
					return  true;
				}
				else if (boundingBox(top, i))
				{
					return true;
				}
				else if (boundingBox(bottom, i))
				{
					return  true;
				}
			}
		}
	}
	return false;
}


void CollisionManager::updateColliders(Vector2 position, int id)
{
	colliders[id].setBoxOrigin(position);

}

void CollisionManager::updateBoundingBox(int id)
{
	top = Vector2(colliders[id].getBoxOrigin().x, colliders[id].getBoxOrigin().y);
	bottom = Vector2(colliders[id].getBoxOrigin().x, colliders[id].getMaxValues().y);
	left = Vector2(colliders[id].getBoxOrigin().x, colliders[id].getBoxOrigin().y);
	right = Vector2(colliders[id].getMaxValues().x, colliders[id].getBoxOrigin().y);
}



void CollisionManager::update()
{
}