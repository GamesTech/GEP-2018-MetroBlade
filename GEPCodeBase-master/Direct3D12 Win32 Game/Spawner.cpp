#include "pch.h"
#include "Spawner.h"
#include "Item.h"
Spawner::Spawner(RenderData* _RD, string filename, Vector2 position, int item_count)
{
	SetPos(position);
	item_counter = item_count;
	render_data = _RD;
	item_vector.resize(item_count);
}

Spawner::~Spawner()
{
}

void Spawner::initObject()
{
	SpawnObject();
}

void Spawner::SpawnObject()
{
	
}

void Spawner::StartSpawnTimer()
{

}

void Spawner::SetOffset(Vector2 new_offset)
{
	spawn_offset = new_offset;
}

void Spawner::CentreOrigin()
{
}

void Spawner::Tick(GameStateData * _GSD)
{	
}

void Spawner::Render(RenderData * _RD)
{
}
