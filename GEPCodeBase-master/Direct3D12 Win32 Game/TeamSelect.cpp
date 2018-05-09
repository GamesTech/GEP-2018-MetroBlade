#include "pch.h"
#include "TeamSelect.h"

void TeamSelect::update(std::vector<Cursor*> cursors, std::vector<UISprite*> teamview, std::vector<std::string> teamview_images)
{
	for (int i = 0; i < cursors.size(); i++)
		if (cursors[i]->getInteract())
		{
			int tag = cursors[i]->getCollided();
			if (tag >= 0) {
				teamview[i]->changeSpriteRect("fighter_spritesheet", teamview_images[tag]);
			}
		}
}

