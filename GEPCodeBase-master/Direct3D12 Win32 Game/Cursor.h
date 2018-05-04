#pragma once
#include "UIObject.h"
#include "InputManager.h"
class UISprite;

class Cursor : public UIObject
{

public:
	Cursor(std::string filename, RenderData* _RD);
	~Cursor() = default;

	void CheckInput(GameStateData* _GSD);
private:
	UISprite * sprite = nullptr;
	int controller_id = 0;
	float speed = 2.0f;

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;
};