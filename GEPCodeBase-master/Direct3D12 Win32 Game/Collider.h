#pragma once
#include "GameObject2D.h"

class Collider
{
public: 
	Collider() = default;
	~Collider();

	void getHeight();
	void getWidth();
	void getXPos();
	void getYPos();

	void setHeight();
	void setWidth();
	void setXPos();
	void setYPos();

	//Vector2 getBoundingBox(RECT& collision_box);
	RECT getBoundingBox();
	
private:
	Vector2  box_dimentions = Vector2(0,0);
	float height = 0;
	float width = 0;
	float xPos = 0;
	float yPos = 0;
};