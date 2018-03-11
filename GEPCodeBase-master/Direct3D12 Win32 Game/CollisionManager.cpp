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

int CollisionManager::checkCollisions()
{
	if (!colliders.empty())
	{
		for (int i = 0; i < colliders.size(); i++)
		{
			for (int j = 0; j < colliders.size(); j++)
			{
				if (i != j)
				{
					if (boundingBox(left, i))
					{
						return 1;
					}
					else if (boundingBox(right, i))
					{
						return 2;
					}
					else if (boundingBox(top, i))
					{
						return 3;
					}
					else if (boundingBox(bottom, i))
					{
						return 4;
					}

				}
			}
		}

	}
	return 0;
}


void CollisionManager::updateColliders(Vector2 position, int id)
{
	colliders[id].setBoxOrigin(position);
	top = Vector2(colliders[id].getBoxOrigin().x, colliders[id].getBoxOrigin().y);
	bottom = Vector2(colliders[id].getBoxOrigin().x, colliders[id].getMaxValues().y);
	left = Vector2(colliders[id].getBoxOrigin().x, colliders[id].getBoxOrigin().y);
	right = Vector2(colliders[id].getMaxValues().x, colliders[id].getBoxOrigin().y);


}

Vector2 CollisionManager::collide()
{
	switch (checkCollisions())
	{
	case 0:
		return Vector2(0, 0);
		break;
	case 1:
		return Vector2(-1, 0);
		break;
	case 2:
		return Vector2(1, 0);
		break;
	case 3:
		return Vector2(0, 1);
		break;
	case 4:
		return Vector2(0, -1);
		break;
	}
}


void CollisionManager::update()
{
	checkCollisions();
}