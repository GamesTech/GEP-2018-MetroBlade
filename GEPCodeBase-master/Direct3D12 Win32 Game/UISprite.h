// Author - Nathan Butt
// Date - 21/03/2018

#pragma once


#include "pch.h"
#include "UIObject.h"
#include "GameStateData.h"


class UISprite : public UIObject
{
public:
	UISprite(std::string filename, RenderData* _RD);
	void setSprite(std::string filename, std::string fighter);
	void CheckInput(GameStateData * _GSD);
	void changeSpriteRect(std::string filename, std::string fighter);
	~UISprite() = default;

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;
	bool getInteract() { return interact; }
	void setInteract(bool interact) { this->interact = interact; }
private:
	DirectX::GamePad::State controller_state;
	bool interact = false;
	bool a_pressed = false;
	Microsoft::WRL::ComPtr<ID3D12Resource>   texture;
	std::shared_ptr<RECT>   src_rect /*= std::make_shared<RECT>()*/;
	int resource_number = -1;
	Collider* col = new Collider(Vector2(m_pos), Vector2(100, 100), true);
	void onCollision(MetroBrawlCollisionData  col_data);
	Sprite* sprite = nullptr;
	int controller_id = 0;
};