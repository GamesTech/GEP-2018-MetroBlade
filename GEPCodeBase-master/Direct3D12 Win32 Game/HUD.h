#pragma once
#include "UILabel.h"

class HUD : public UIObject
{
public:
	HUD();
	~HUD() = default;

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;
	void updateLabels(std::vector<UILabel*> labels);

private:
};