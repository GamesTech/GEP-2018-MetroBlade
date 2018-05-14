/**
*  @file    PhysicsResolver.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    03/05/2018
*  @version v1.0
*
*  @section System Module
*           Core State Manager.
*
*  @brief Definition for the Physcis Resolver. 
*
*  @section Description
*
*  This is a component of the collision manager and is risponcable for managing physics of all objects in the game.
*/


#pragma once

#include "pch.h"

class MetroBrawlPhysicsResolver 
{
public:
	MetroBrawlPhysicsResolver() = default;
	~MetroBrawlPhysicsResolver() = default;

	void resolveObjectCollision(Collider& a, Collider& b);

private:
	// Here we calculate our normals etc and based on this we will then add force to the object etc.
	Vector2 calculateCollisionNormal(Collider a, Collider b);
	Vector2 calculateCollisionPoint(Collider a, Collider b);
};