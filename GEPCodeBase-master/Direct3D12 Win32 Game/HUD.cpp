#include "pch.h"
#include "HUD.h"


void HUD::Tick(GameStateData * _GSD)
{
}

void HUD::Render(RenderData * _RD)
{
}

void HUD::addLabel(UILabel* player_labels)
{
	labels.push_back(player_labels);
}

void HUD::updateLabels()
{
	//for (int i = 0; i < 4; i++)
	//{
	//	//Updates the text based on player numbers and each individuals health.
	//	player_labels[i]->setText(std::to_string(scene.getScene()->->getPlayerHealth()) += "%");
	//}
	//if (!player_labels.empty())
	//{

	//}
}
