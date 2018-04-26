#include "pch.h"
#include "Item.h"

Item::Item(RenderData* _RD, string _filename) : ImageGO2D(_RD, _filename)
{
	CentreOrigin();
}

Item::~Item()
{
}

void Item::SetPosition(Vector2 new_pos)
{
	pos = new_pos;
}