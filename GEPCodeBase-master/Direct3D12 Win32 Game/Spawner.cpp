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
	for (int i = 0; i < item_counter; i++)
	{
		int random = 0;
		switch (i)
		{
		case HEALTH:
			item_vector[i] = new Item(render_data, "bubble_item", ItemType::HEALTH);
			item_vector[i]->SetPos(Vector2(400, 550));
			world.instantiateToScene(item_vector[i]);
			break;
		case PROJECTILE:
			item_vector[i] = new Item(render_data, "bubble_item", ItemType::PROJECTILE);
			item_vector[i]->SetPos(Vector2(400, 475));
			world.instantiateToScene(item_vector[i]);
			break;
		case HAMMER:
			item_vector[i] = new Item(render_data, "bubble_item", ItemType::HAMMER);
			item_vector[i]->SetPos(Vector2(400, 400));
			world.instantiateToScene(item_vector[i]);
			break;
		case BOMB:
			item_vector[i] = new Item(render_data, "bubble_item", ItemType::BOMB);
			item_vector[i]->SetPos(Vector2(400, 325));
			world.instantiateToScene(item_vector[i]);
			break;
		}
	}
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
