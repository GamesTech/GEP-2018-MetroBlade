#pragma once
#include "GameObject2D.h"

class Collider
{
public: 
	Collider() = default;
	~Collider();

	RECT getBoundingBox() const;

private: 
	
};