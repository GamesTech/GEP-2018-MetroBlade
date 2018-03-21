#include "pch.h"
#include "LobbySystem.h"

void LobbySystemComponent::addLobbyReference(std::vector<PlayerData>* player_lobby)
{
	lobby_refrence = player_lobby;
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
	lobby_refrence->push_back(new_player);
}

void LobbySystemComponent::checkPlayers()
{
	return;
}

PlayerData LobbySystemComponent::getPlayerByIndex(int index)
{
	return (*lobby_refrence)[index];
}
