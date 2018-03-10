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

bool CollisionManager::checkCollisions()
{
	if (!colliders.empty())
	{
		for (int i = 0; i < colliders.size(); i++)
		{
			for (int j = 0; j < colliders.size(); j++)
			{
				if (i != j)
				{
					if (colliders[j].getBoxOrigin().x <= colliders[i].getMaxValues().x 
						&& colliders[j].getBoxOrigin().x >= colliders[i].getBoxOrigin().x
						&&colliders[j].getBoxOrigin().y >= colliders[i].getBoxOrigin().y
						&& colliders[j].getBoxOrigin().y <= colliders[i].getMaxValues().y)
					{
						return true;
					}
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



void CollisionManager::update()
{
	checkCollisions();
}