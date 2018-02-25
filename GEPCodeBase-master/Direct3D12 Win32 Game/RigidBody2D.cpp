#include "RigidBody2D.h"
#include "Physics2D.h"

void RigidBody2D::gravity()
{
	physics_object.AddForce(10 * Vector2::UnitY);
}
