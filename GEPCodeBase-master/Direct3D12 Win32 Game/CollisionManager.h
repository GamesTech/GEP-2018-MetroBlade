#pragma once
#include "Collider.h"
#include "Player2D.h"
class CollisionManager
{
private:
	std::vector<Collider> colliders;
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	void init();

	void addCollider(Collider collider);
	void updateColliders(Vector2 position, int id);
	void update();
	bool checkCollisions(int id);
	Vector2 collide();
};
