// Author - Nathan Butt
// Date - 21/03/2018

#pragma once


#include "pch.h"
#include "UIObject.h"


class UISprite : public UIObject 
{
public:
	UISprite() = default;
	~UISprite() = default;

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;

private:
	Microsoft::WRL::ComPtr<ID3D12Resource>   game_texture;
};