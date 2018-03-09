#include "pch.h"

#include "CollisionManager.h"

void CollisionManager::getCollider(Collider collider)
{
	current_collider->getMaxX();
}

void CollisionManager::addCollider(Collider collider)
{
	colliders.reserve(100);
	colliders.push_back(collider);
}
