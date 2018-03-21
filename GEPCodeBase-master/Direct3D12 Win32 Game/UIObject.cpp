#include "pch.h"
#include "UIObject.h"

void UIObject::CentreOrigin()
{
}

void UIObject::Tick(GameStateData * _GSD)
{
}

void UIObject::Render(RenderData * _RD)
{
}

void UIObject::setCanvasPosition(Vector2 new_position)
{
	canvas_position = new_position;
}

Vector2 UIObject::getCanvasPosition() const
{
	return canvas_position;
}
