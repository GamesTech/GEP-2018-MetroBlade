#include "pch.h"
#include "Item.h"

Item::Item(RenderData* _RD, string _filename, ItemType type) : ImageGO2D(_RD, _filename)
{
	item_type = type;
	CentreOrigin();
}

Item::~Item()
{
}

void Item::SetPosition(Vector2 new_pos)
{
	pos = new_pos;
}

void Item::Tick(GameStateData* _GSD)
{
	//physics stuff, need new physics before implementing as old inherits from image
}

void Item::UseItem(Player2D* player, ItemType type)
{
	switch (type)
	{
	case HEALTH:
		player->health += 25;
		break;
	}

}