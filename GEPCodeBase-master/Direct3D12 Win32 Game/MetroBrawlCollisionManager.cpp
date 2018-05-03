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
			checkColliders(*col);
		}
	}
}

void MetroBrawlCollisionManager::clearCollisionManager()
{
	object_colliders.clear();
}

void MetroBrawlCollisionManager::checkColliders(Collider& col)
{
	for (int i = 0; i < object_colliders.size(); i++) 
	{
		if ((object_colliders[i] != &col) && (object_colliders[i]->isColliderActive())) 
		{
			if (collisionTest(col, *object_colliders[i])) 
			{
				MetroBrawlCollisionData   col_event;
				// Here we send the events to the player objects. 

				col_event.collider_object = object_colliders[i];
				col.OnCollision(col_event);

				col_event.collider_object = &col;
				object_colliders[i]->OnCollision(col_event);
			}
		}
	}
}

bool MetroBrawlCollisionManager::collisionTest(Collider& a, Collider& b)
{
	if ((a.getMaxValues().x > b.getBoxOrigin().x) && 
		(b.getMaxValues().x > a.getBoxOrigin().x)) 
	{
		if ((a.getMaxValues().y > b.getBoxOrigin().y) && 
			(b.getMaxValues().y > a.getBoxOrigin().y))
		{
			return true;
		}
	}

	return false;
}
