#include "pch.h"
#include "HUD.h"



void HUD::Tick(GameStateData * _GSD)
{

}

void HUD::Render(RenderData * _RD)
{
	if (!labels.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			labels[i]->Render(_RD);
		}
	}
}

void HUD::addLabel(UILabel* player_labels)
{
	labels.push_back(player_labels);
}

void HUD::updateLabels(std::vector<UILabel*> labels)
{
	if (!labels.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			//Updates the text based on player numbers and each individuals health.
			labels[i]->setText(std::to_string(1) + "%");
		}
	}
}

void HUD::clear()
{
	labels.clear();
}
