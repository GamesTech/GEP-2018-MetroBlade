#pragma once
#include "UILabel.h"

class HUD : public UIObject
{
public:
	HUD() = default;
	~HUD() = default;

	void Tick(GameStateData * _GSD) override;
	void Render(RenderData * _RD) override;
	void addLabel(UILabel* player_labels);
	void updateLabels(std::vector<UILabel*> labels);
	void clear();
	std::vector<UILabel*> getLabels() { return labels; }
private:
	std::vector<UILabel*> labels;
};