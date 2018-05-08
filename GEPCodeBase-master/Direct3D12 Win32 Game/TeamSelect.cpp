#include "pch.h"
#include "TeamSelect.h"

void TeamSelect::update(std::vector<Cursor*> cursors, std::vector<UISprite*> profile_pics, std::vector<UISprite*> teamview, std::vector<std::string> teamview_images)
{
	for (int i = 0; i < cursors.size(); i++)
		if (cursors[i]->getInteract())
		{
			for (int j = 0; j < profile_pics.size(); j++)
			{
				if (profile_pics[j]->getInteract())
				{
					teamview[i]->changeSpriteRect("fighter_spritesheet", teamview_images[j]);
					profile_pics[j]->setInteract(false);
				}
			}
		}
}

