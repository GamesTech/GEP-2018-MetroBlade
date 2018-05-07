// Author - Nathan Butt
// Date - 21/03/2018

#pragma once


#include "pch.h"
#include "UIObject.h"


class UISprite : public UIObject
{
public:
	UISprite(std::string filename, RenderData* _RD);
	~UISprite();

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;
	bool getInteract() { return interact; }
	void setInteract(bool interact) { this->interact = interact; }
	void setRECT(float left, float top, float right, float bottom);
private:
	DirectX::GamePad::State controller_state;
	bool interact = false;
	bool a_pressed = false;
	Microsoft::WRL::ComPtr<ID3D12Resource>   texture;
	std::shared_ptr<RECT>   src_rect;
	int resource_number = -1;
	Collider* col = new Collider(Vector2(m_pos), Vector2(100, 100), true);
	void onCollision(MetroBrawlCollisionData  col_data);
	
	RECT *test = src_rect.get();
};