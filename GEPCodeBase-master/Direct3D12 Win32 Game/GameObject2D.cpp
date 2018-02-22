#include "pch.h"
#include "GameObject2D.h"


GameObject2D::GameObject2D()
{
}


GameObject2D::~GameObject2D()
{
}


RECT GameObject2D::getBoundingBox()
{
	RECT bounding_box;

	bounding_box.top = m_pos.y;
	bounding_box.left = m_pos.x;

}

