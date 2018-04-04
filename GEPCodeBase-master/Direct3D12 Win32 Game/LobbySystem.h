/**
*  @file    LobbySystem.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    14/03/2018
*  @version v1.0
*
*  @section System Module
*           Game Lobby System
*
*  @brief Definition for the AnimationData structure
*
*  @section Description
*
*  Component used for interfacing with the lobby system. Allows Players to join and leave the game at any time.
*/


#pragma once


#include "pch.h"
#include "GameComponent.h"
#include "PlayerData.h"

class LobbySystemComponent : public GameComponent 
{
public:
	LobbySystemComponent() = default;
	~LobbySystemComponent() = default;

	void addLobbyReference(std::vector<PlayerData>*  player_lobby);

	// Inherited via GameComponent
	virtual void tickComponent(GameStateData * _GSD) override;
	virtual void renderComponent(RenderData * _RD) override;

	// Utility Functions
	void addPlayer(PlayerData new_player); //< add player to the lobby.
	bool isPlayerRegistered(int controller_id); //< Checks to see if the player is already registered and if so do nothing.  
	void checkPlayersActivity(); ///< Checks a player to see if there controller is still active and if not, then remove them (Unimplimented.)

	PlayerData getPlayerByIndex(int index);

private:
	std::vector<PlayerData>*		lobby_refrence;
};