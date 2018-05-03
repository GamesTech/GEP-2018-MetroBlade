/**
*  @file    MetroBrawlCollisionData.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    01/05/2018
*  @version v1.0
*
*  @section System Module
*           Core State Manager.
*
*  @brief Definition for the Collision Data
*
*  @section Description
*
*  This is used by the collision manager to send data about the collision to the objects.
*/

#pragma once

class Collider;

struct MetroBrawlCollisionData 
{
	Collider*  collider_object = nullptr;
};