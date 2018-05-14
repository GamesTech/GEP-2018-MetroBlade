#include "pch.h"
#include "HUD.h"
#include "LobbySystem.h"



HUD::HUD()
{
	object_components.addComponent(new LobbySystemComponent);
}

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
	PlayerStatus* dmg = nullptr;
	if (!labels.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			//Updates the text based on player numbers and each individuals health.
			dmg = object_components.getComponentByType<LobbySystemComponent>()->getPlayerStatusByIndex(i);

			if (dmg) 
			{
				labels[i]->setText(std::to_string(dmg->getDamagePercentage()) + "%");
			}
		}
	}
}

void HUD::clear()
{
	labels.clear();
}
