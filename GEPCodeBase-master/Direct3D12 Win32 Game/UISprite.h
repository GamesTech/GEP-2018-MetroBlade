// Author - Nathan Butt
// Date - 21/03/2018

#pragma once


#include "pch.h"
#include "UIObject.h"


class UISprite : public UIObject 
{
public:
	UISprite(std::string filename, RenderData* _RD);
	~UISprite() = default;

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;

private:
	Microsoft::WRL::ComPtr<ID3D12Resource>   texture;
	std::shared_ptr<RECT>   src_rect;
	int resource_number = -1;
};