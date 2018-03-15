#pragma once

#include <string>

#include "GameComponent.h"

class TestComponent : public GameComponent 
{
public:
	TestComponent() = default;

	void tickComponent(GameStateData*  _GSD) override {};
	void renderComponent(RenderData*     _RD) override {};

	void print() { OutputDebugString(L"A message lol \n"); }
};