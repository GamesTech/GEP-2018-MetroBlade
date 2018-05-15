#pragma once
#include "Physics2D.h"
#include "Sprite.h"
//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite

class Obstacle2D
	: public ImageGO2D

{
public:
	//TODO: add a 3d player and modes to switch between different views and basic physics
	Obstacle2D(RenderData* _RD, string _filename, Vector2 dimensions);
	virtual ~Obstacle2D();
	virtual void Tick(GameStateData* _GSD);

	Vector2 direction = Vector2(0, 0);


protected:
	Sprite*				sprite;
	Collider * col = nullptr;

	void onObjectCollision(MetroBrawlCollisionData	col_data);
};