#pragma once
#include "ImageGO2D.h"

enum ItemType {
	NONE,
	SPEED,
	HEALTH,
};

class Item : public ImageGO2D
{
public:
	Item(RenderData* _RD, string _filename, ItemType type);
	virtual ~Item();

	Vector2 GetPostion() { return pos; }
	void SetPosition(Vector2 new_pos);
	virtual void Tick(GameStateData* _GSD);
private:
	Vector2 pos = Vector2::Zero;
	ItemType item_type = ItemType::NONE;
};