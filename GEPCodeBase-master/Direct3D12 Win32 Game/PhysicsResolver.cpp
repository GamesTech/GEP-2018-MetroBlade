#include "pch.h"

#include "Physics2D.h"
#include "PhysicsResolver.h"

void MetroBrawlPhysicsResolver::resolveObjectCollision(Collider& a, Collider& b)
{
	
}

Vector2 MetroBrawlPhysicsResolver::calculateCollisionNormal(Collider a, Collider b)
{
	// Here we will calculate the collision normal and then based on this we will
	// move the player based on the players positional delta.

	// We will also need to add code to have control over this collision. 
	// Base this on a bitflag.

	return Vector2(1.0f, 0.0f);
}
