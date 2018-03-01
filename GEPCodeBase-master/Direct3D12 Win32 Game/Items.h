#pragma once
#include "GameObject2D.h"
#include "Physics2D.h"
class Items : Physics2D
{
public:
	Items(RenderData* _RD, string _filename);
	~Items() = default;
	virtual void Tick(GameStateData* _GSD);
private:
	Vector2 pos;
	enum ItemTypes { SPEEDBOOST };
};