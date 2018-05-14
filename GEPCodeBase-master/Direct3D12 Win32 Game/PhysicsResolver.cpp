#include "pch.h"

#include "Player2D.h"
#include "Physics2D.h"
#include "PhysicsResolver.h"

void MetroBrawlPhysicsResolver::resolveObjectCollision(Collider& a, Collider& b)
{
	Physics2D*   physics_object = dynamic_cast<Physics2D*>(a.getCollidersParent());
	
	if (physics_object && !dynamic_cast<Player2D*>(b.getCollidersParent()))
	{
		Vector2 collision_normal = calculateCollisionNormal(a, b);
		Vector2 collision_point = calculateCollisionPoint(a, b);

		// Get the delta of there position.
		// a.getCollidersParent()->SetPos(a.getCollidersParent()->GetPos() + Vector2(physics_object->getDeltaPos().x * -collision_normal.x, physics_object->getDeltaPos().y * -collision_normal.y));
		// a.getCollidersParent()->SetPos(a.getCollidersParent()->GetPos() - collision_point);

		 physics_object->SetVel(Vector2(-physics_object->GetVel().x * collision_normal.x, -physics_object->GetVel().y * collision_normal.y));
		//physics_object->AddForce(Vector2(-physics_object->GetVel().x * collision_normal.x, -physics_object->GetVel().y * collision_normal.y));
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

	collision_normal = Vector2 // TODO - Consider removing as it isnt needed. 
	(
		(bool)(collision_point.x >= collision_point.y),
		(bool)(collision_point.y >= collision_point.x)
	);

	return collision_point;
}

Vector2 MetroBrawlPhysicsResolver::calculateCollisionPoint(Collider a, Collider b)
{
	Vector2  collision_point = (b.getBoxMidpoint() - a.getBoxMidpoint()) - (b.getBoxMidpoint() - b.getBoxOrigin());
	return  collision_point;
}
