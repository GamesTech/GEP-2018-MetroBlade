#pragma once
#include "Collider.h"
#include "Player2D.h"
class CollisionManager
{
private:
	std::vector<Collider> colliders;
	/*std::unique_ptr<Collider>  current_collider;*/
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	void init();

	void addCollider(Collider collider);
	bool checkCollisions();
	void updateColliders(Vector2 position, int id);
	void update();
};
