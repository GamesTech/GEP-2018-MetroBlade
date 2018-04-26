#pragma once
#include "ImageGO2D.h"
class Item : public ImageGO2D
{
public:
	Item(RenderData* _RD, string _filename);
	virtual ~Item();

	Vector2 GetPostion() { return pos; }
	void SetPosition(Vector2 new_pos);
private:
	Vector2 pos = Vector2::Zero;
};