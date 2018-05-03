#include "pch.h"
#include "Obstacle2D.h"
#include "GameStateData.h"
#include "PlayerStatus.h"

#include "Sprite.h"
#include "SpriteAnimFileReader.h"


Obstacle2D::Obstacle2D(RenderData* _RD, string _filename): ImageGO2D(_RD, _filename)
{
	col->isColliderActive(true);
	col->addParentObjectRefrence(this);
	object_components.addComponent(col);
}


Obstacle2D::~Obstacle2D()
{
}

void Obstacle2D::Tick(GameStateData* _GSD)
{
	col->setBoxOrigin(Vector2(m_pos));
	m_origin = Vector2(100,100);
	
	//change anim depending

	//GEP:: Lets go up the inheritance and share our functionality
}


Collider* Obstacle2D::getCollider(int id)
{

	switch (id)
	{
	case 0:
		return col;
		break;
	}
	return nullptr;
}


