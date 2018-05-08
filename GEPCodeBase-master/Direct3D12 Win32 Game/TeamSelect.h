#pragma once

#include "GameObject2D.h"
#include "UISprite.h"
#include "Cursor.h"

class TeamSelect : public GameObject2D
{
public:
	TeamSelect() = default;
	~TeamSelect() = default;

	void Tick(GameStateData * _GSD) override;
	void update(std::vector<Cursor*> cursors, std::vector<UISprite*> profile_pics , std::vector<UISprite*> teamview, std::vector<std::string> teamview_images);
};