#include "pch.h"
#include "PlayerController.h"

PlayerController::PlayerController(std::vector<PlayerData>* player_register)
	:player_data_buffer(player_register)
{
}

void PlayerController::tickComponent(GameStateData * _GSD)
{
	return;
}

void PlayerController::renderComponent(RenderData * _RD)
{
	return;
}
