#pragma once
#include "pch.h"
#include "GameObject2D.h"
#include <vector>
class Spawner : public GameObject2D
{
public:
	Spawner(RenderData* _RD, string filename, Vector2 position, int item_count);
	~Spawner();
	void SpawnObject();
	void StartSpawnTimer();
	void SetOffset(Vector2 new_offset);

	// Inherited via GameObject2D
	virtual void CentreOrigin() override;
	virtual void Tick(GameStateData * _GSD) override;
	virtual void Render(RenderData * _RD) override;


private:
	RenderData* render_data = nullptr;
	int item_counter = 0;
	bool item_created = false;
	std::vector<Item*> item_vector;
	GameObject2D* spawn_object;
	Vector2 spawn_offset;
};