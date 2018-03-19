#include "pch.h"

#include "GameStateData.h"
#include "RenderData.h"

#include "UILabel.h"

void UILabel::setText(std::string new_text)
{
	text = std::wstring(L"test");
}

void UILabel::Tick(GameStateData* _GSD)
{
}

void UILabel::Render(RenderData* _RD)
{
	_RD->m_font->DrawString(_RD->m_spriteBatch.get(), text.c_str(), Vector2(600, 600));
}
