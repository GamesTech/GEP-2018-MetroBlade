#include "pch.h"

#include "Player2D.h"
#include "Physics2D.h"
#include "PhysicsResolver.h"

void MetroBrawlPhysicsResolver::resolveObjectCollision(Collider& a, Collider& b)
{
	Physics2D*   physics_object = dynamic_cast<Physics2D*>(a.getCollidersParent());
	
	if (physics_object)
	{
		Vector2 collision_normal = calculateCollisionNormal(a, b);

		a.getCollidersParent()->SetPos(a.getCollidersParent()->GetPos() + Vector2(0, -0.1));
		physics_object->SetVel(Vector2::Zero);
	}

	if (dynamic_cast<Player2D*>(a.getCollidersParent())) 
	{
		((Player2D*)a.getCollidersParent())->setStateGrounded();
	}
}

Vector2 MetroBrawlPhysicsResolver::calculateCollisionNormal(Collider a, Collider b)
{
	// Here we will calculate the collision normal and then based on this we will
	// move the player based on the players positional delta.

	// We will also need to add code to have control over this collision. 
	// Base this on a bitflag.

	Vector2 collision_normal = Vector2::Zero;

	Vector2  b_midpoint = b.getBoxMidpoint();
	Vector2  collision_point = (b_midpoint - a.getBoxMidpoint()) - (b_midpoint - b.getBoxOrigin());

	collision_point.Normalize();

	collision_normal = Vector2
	(
		(bool)(collision_point.x >= collision_point.y),
		(bool)(collision_point.y >= collision_point.x)
	);

	return collision_normal;
}
