#pragma once
#include "GameComponent.h"

class Layers : public GameComponent
{
public:
	Layers() = default;
	~Layers() = default;

	void renderLayers(RenderData * _RD);
	int getXPos();
	int getYPos();

private:
	int xPos;
	int yPos;
};