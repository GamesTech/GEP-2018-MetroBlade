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

