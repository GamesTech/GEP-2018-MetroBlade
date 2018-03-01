#include "pch.h"
#include "Items.h"
Items::Items(RenderData* _RD, string _filename) :Physics2D(_RD, _filename)
{
	CentreOrigin();
}

void Items::Tick(GameStateData * _GSD)
{

	//GEP:: Lets go up the inheritence and share our functionality

	Physics2D::Tick(_GSD);
}