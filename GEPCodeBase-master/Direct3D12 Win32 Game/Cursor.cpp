#include "pch.h"
#include "Cursor.h"
#include "UISprite.h"
#include "RenderData.h"
#include "GameStateData.h"

Cursor::Cursor(std::string filename, RenderData * _RD)
{
	sprite = new UISprite(filename, _RD);
}

void Cursor::CheckInput(GameStateData * _GSD)
{
	DirectX::GamePad::State controller_state = _GSD->m_gamePad->GetState(controller_id);

	float stick_x = controller_state.thumbSticks.leftX;
	float stick_y = controller_state.thumbSticks.leftY;

	SetPos(Vector2(GetPos().x + (stick_x*speed), GetPos().y - (stick_y*speed)));

	sprite->SetPos(GetPos());
}

void Cursor::Tick(GameStateData * _GSD)
{
	CheckInput(_GSD);
}

void Cursor::Render(RenderData * _RD)
{
	sprite->Render(_RD);
}
