#pragma once
#include "Collider.h"
#include "Player2D.h"
class CollisionManager
{
private:
	std::vector<Collider*> colliders;
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
	bool checkTrigger(int id);
};
