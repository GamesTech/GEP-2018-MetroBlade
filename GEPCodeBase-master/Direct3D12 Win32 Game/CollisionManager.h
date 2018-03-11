#pragma once
#include "Collider.h"
#include "Player2D.h"
class CollisionManager
{
private:
	std::vector<Collider> colliders;
	Vector2 left;
	Vector2 right;
	Vector2 top;
	Vector2 bottom;
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	void init();

	void addCollider(Collider collider);
	bool boundingBox(Vector2 wallType, int rect2ID);
	void updateColliders(Vector2 position, int id);
	void update();
	int checkCollisions();
	Vector2 collide();
};
