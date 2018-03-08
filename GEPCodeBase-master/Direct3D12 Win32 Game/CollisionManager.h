#pragma once

class CollisionManager
{
private:
	std::vector<Collider*> colliders;
public:
	CollisionManager() = default;
	~CollisionManager() = default;
	void getCollider(Collider collider);

};