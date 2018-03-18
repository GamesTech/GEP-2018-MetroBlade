#include "pch.h"
#include "CollisionManager.h"


void CollisionManager::init()
{
	colliders.reserve(20);
}
void CollisionManager::addCollider(Collider* collider)
{
	colliders.push_back(collider);
}

int CollisionManager::GetSize()
{
	return colliders.size();
}

int CollisionManager::checkCollisions(int id)
{
	if (!colliders.empty())
	{
		for (int i = 0; i < colliders.size(); i++)
		{
			if (id != i && colliders[id]->getTag() != colliders[i]->getTag())
			{
				if (colliders[id]->getBoxOrigin().x <= colliders[i]->getMaxValues().x &&
					colliders[id]->getMaxValues().x >= colliders[i]->getBoxOrigin().x &&
					colliders[id]->getBoxOrigin().y <= colliders[i]->getMaxValues().y &&
					colliders[id]->getMaxValues().y >= colliders[i]->getBoxOrigin().y)
				{
					if (!checkTrigger(i))
					{
						return  colliders[id]->getTag();
					}
				}
			}
		}
	}
	return -1;
}

bool CollisionManager::checkTrigger(int id)
{
	if (colliders[id]->getTrigger())
	{
		return true;
	}
	return false;
}

void CollisionManager::updateColliders(Vector2 position, int id)
{
	colliders[id]->setBoxOrigin(position);
}

void CollisionManager::update()
{
}

int CollisionManager::getTag(int id)
{
	return colliders[id]->getTag();
}