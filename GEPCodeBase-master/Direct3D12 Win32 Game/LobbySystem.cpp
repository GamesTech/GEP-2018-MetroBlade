#include "pch.h"

#include "GameManager.h"

#include "LobbySystem.h"

void LobbySystemComponent::addLobbyReference(std::vector<PlayerData>* player_lobby)
{
	lobby_refrence = player_lobby;
}

void LobbySystemComponent::addLobbyRefrence(GameManager* game_manager)
{
	game_state = game_manager;
}

void LobbySystemComponent::tickComponent(GameStateData* _GSD)
{
	return;
}

void LobbySystemComponent::renderComponent(RenderData* _RD)
{
	return;
}

void LobbySystemComponent::addPlayer(PlayerData new_player)
{
	// TODO - Consider Adding Error Checking Here.
	game_state->getPlayerLobbyData()->push_back(new_player);
}

bool LobbySystemComponent::isPlayerRegistered(int controller_id)
{
	for (auto& player : *lobby_refrence) 
	{
		if (player.input_device_id == controller_id) 
		{
			return true;
		}
	}

	return false;
}

void LobbySystemComponent::checkPlayersActivity()
{
	return;
}

void LobbySystemComponent::startGameManager()
{
	game_state->startGame();
}

PlayerData LobbySystemComponent::getPlayerByIndex(int index)
{
	return (*lobby_refrence)[index];
}

PlayerStatus* LobbySystemComponent::getPlayerStatusByIndex(int index)
{
	return game_state->getPlayerInstanceStatus(index);
}
