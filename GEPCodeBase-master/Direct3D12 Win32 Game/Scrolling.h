#pragma once
#include "GameComponent.h"

class Scrolling : public GameComponent
{
public:
	Scrolling() = default;
	~Scrolling() = default;

	void loadImages();
	void renderImages(RenderData * _RD);

	//Created vector of layers;
	//Each layer based upon distance from 

};