#include "pch.h"
#include "UITest.h"

UITest::UITest(RenderData * _RD)
{
	testImage = std::make_unique<ImageGO2D>(_RD, "gens");
}

void UITest::Tick(GameStateData * _GSD)
{
	return;
}

void UITest::Render(RenderData * _RD)
{
	testImage->Render(_RD);
}
