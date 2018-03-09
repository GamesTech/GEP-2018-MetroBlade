#pragma once
#include "Collider.h"

class CollisionManager
{
private:
	std::vector<Collider> colliders;
	std::unique_ptr<Collider>  current_collider;
public:
	CollisionManager() = default;
	~CollisionManager() = default;
	void getCollider(Collider collider);
	void addCollider(Collider collider);
};
