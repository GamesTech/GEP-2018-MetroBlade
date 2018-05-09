/**
*  @file    Cursor.h
*  @author  Jack Watson (GitHub - JackW8335)
*  @date    09/05/2018
*  @version v1.0
*
*  @section System Module
*           TeamSelect UI
*
*  @brief Defines a TeamSelect Object.
*
*  @section Description
*
* A class created to store the logic from game.cpp inside an object.
*/
#pragma once

#include "GameObject2D.h"
#include "UISprite.h"
#include "Cursor.h"

class TeamSelect : public GameObject2D
{
public:
	TeamSelect();
	~TeamSelect() = default;
	void update(std::vector<Cursor*> cursors, std::vector<UISprite*> teamview, std::vector<std::string> teamview_images);
	std::vector<int> getTeamSelection() { return teamSelection; }

	void CentreOrigin() override;
	 void Tick(GameStateData* _GSD) override;
	 void Render(RenderData* _RD) override;

private:
	std::vector<int> teamSelection;
	int tag = -1;
};