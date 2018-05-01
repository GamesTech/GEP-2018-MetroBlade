#include "pch.h"
#include "MetroBrawlCollisionManager.h"

constexpr int COLLIDER_RESERVE = 100;

MetroBrawlCollisionManager::MetroBrawlCollisionManager()
{
	object_colliders.reserve(COLLIDER_RESERVE);
}

void MetroBrawlCollisionManager::registerObjectCollider(Collider* object_col)
{
	object_colliders.push_back(object_col);
}

void MetroBrawlCollisionManager::registerObjectColliders(std::vector<Collider*> object_cols)
{
	for (auto& col : object_cols) 
	{
		object_colliders.push_back(col);
	}
}

void MetroBrawlCollisionManager::performCollisionCheck()
{
	for (auto& col : object_colliders) 
	{
		if (col->isColliderImmediate()) 
		{
			// TODO - Add code to perform collision checks.
		}
	}
}

bool MetroBrawlCollisionManager::collisionTest(Collider a, Collider b)
{
	return false;
}
