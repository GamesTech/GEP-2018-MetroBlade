#include "pch.h"
#include "TeamSelect.h"


TeamSelect::TeamSelect()
{
	teamSelection.reserve(4);
	teamSelection.resize(4);
	std::fill(teamSelection.begin(), teamSelection.end(), -1);
}

void TeamSelect::update(std::vector<Cursor*> cursors, std::vector<UISprite*> teamview, std::vector<std::string> teamview_images)
{
	for (int i = 0; i < cursors.size(); i++)
		if (cursors[i]->getInteract())
		{
			 tag = cursors[i]->getCollided();
			if (tag >= 0 && tag < 64) {
				teamview[i]->changeSpriteRect("fighter_spritesheet", teamview_images[tag]);
				PlayerData  new_player;
				new_player.character_name = teamview_images[tag];
				cursors[i]->setPlayerData(new_player);
				teamSelection[i] = tag;
			}
		}
}

void TeamSelect::CentreOrigin()
{
}

void TeamSelect::Tick(GameStateData * _GSD)
{
}

void TeamSelect::Render(RenderData * _RD)
{
}



