#include "pch.h"
#include "Obstacle2D.h"
#include "GameStateData.h"
#include "PlayerStatus.h"

#include "Sprite.h"
#include "SpriteAnimFileReader.h"


Obstacle2D::Obstacle2D(RenderData* _RD, string _filename)
{

}


Obstacle2D::~Obstacle2D()
{
}

void Obstacle2D::Tick(GameStateData* _GSD)
{
	col->setBoxOrigin(m_pos);

	//change anim depending

	//GEP:: Lets go up the inheritance and share our functionality

	Physics2D::Tick(_GSD);

}


Collider* Obstacle2D::getCollider(int id)
{

	switch (id)
	{
	case 0:
		//return col;
		break;
	}
	return nullptr;
}


