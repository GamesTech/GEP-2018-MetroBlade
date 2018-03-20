#include "pch.h"

#include "GameStateData.h"
#include "RenderData.h"

#include "UILabel.h"

void UILabel::setText(std::string new_text)
{
	text = std::wstring(L"Super Open Smash");
	canvas_position = Vector2(0.5, 0.1);
}

void UILabel::Tick(GameStateData* _GSD)
{
}

void UILabel::Render(RenderData* _RD)
{
	Vector2 viewport = _RD->m_cam->get2DViewport();
	Vector2 render_position = Vector2(canvas_position.x * viewport.x, canvas_position.y * viewport.y);

	_RD->m_font->DrawString(_RD->m_spriteBatch.get(), text.c_str(), render_position);
}
