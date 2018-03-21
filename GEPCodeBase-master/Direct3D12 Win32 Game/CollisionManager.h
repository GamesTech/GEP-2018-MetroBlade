#pragma once
#include "Collider.h"
#include "Player2D.h"
class CollisionManager
{
private:
	std::vector<Collider*> colliders;

	Vector2 x_overlap;
	Vector2 y_overlap;
	Vector2 overlap;
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	void init();

	void addCollider(Collider* collider);
	int GetSize();
	void updateColliders(Vector2 position, int id);
	void update();
	int getTag(int id);
	int checkCollisions(int id);
	Vector2 colliderOverlap();
	bool checkTrigger(int id);
};
