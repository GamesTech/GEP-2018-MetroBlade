#pragma once
#include "pch.h"
#include "GameObject2D.h"
class Spawner
{
public:
	Spawner();
	~Spawner();
	void SpawnObject();
	void StartSpawnTimer();
	void SetOffset(Vector2 new_offset);
private:

	GameObject2D* spawn_object;
	Vector2 spawn_offset;
};