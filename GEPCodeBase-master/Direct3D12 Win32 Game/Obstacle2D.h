#pragma once
#include "Physics2D.h"
#include "Sprite.h"
//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite

class Obstacle2D
	: public ImageGO2D

{
public:
	//TODO: add a 3d player and modes to switch between different views and basic physics
	Obstacle2D(RenderData* _RD, string _filename);
	virtual ~Obstacle2D();
	virtual void Tick(GameStateData* _GSD);

	Collider* getCollider(int id);

	Vector2 direction = Vector2(0, 0);


protected:
	Collider * col = new Collider(Vector2(m_pos), Vector2(100, 100), false);
};