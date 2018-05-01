/**
*  @file    MetroBrawlCollisionManager.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    01/05/2018
*  @version v1.0
*
*  @section System Module
*           Core State Manager.
*
*  @brief Definition for the Collision Manager
*
*  @section Description
*
*  This is a reimplimentation of the collision manager which is designed to be more flexable and allow for a more effective physics system. 
*/


#pragma once

#include "pch.h"
#include "Collider.h"


class MetroBrawlCollisionManager 
{
public:
	MetroBrawlCollisionManager();
	~MetroBrawlCollisionManager() = default;

	void registerObjectCollider(Collider*  object_col);
	void registerObjectColliders(std::vector<Collider*>  object_cols);

	void performCollisionCheck();



private:
	bool collisionTest(Collider a, Collider b);

	std::vector<Collider*>	object_colliders;
};