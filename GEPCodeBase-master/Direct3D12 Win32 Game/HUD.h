#pragma once
#include "UILabel.h"

class HUD : UIObject
{
public:
	HUD() = default;
	~HUD() = default;

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;
	void addLabel(UILabel* player_labels);
	void updateLabels();
private:
	std::vector<UILabel*> labels;
};