// TODO - Add information here

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
	void addPlayer(PlayerData new_player); 
	void checkPlayers(); ///< Checks a player to see if there controller is still active and if not, then remove them (Unimplimented.)

	PlayerData getPlayerByIndex(int index);

private:
	std::vector<PlayerData>*		lobby_refrence;
};