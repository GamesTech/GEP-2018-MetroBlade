/**
*  @file    GameManager.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    11/03/2018
*  @version v1.0
*
*  @section System Module
*           Core State Manager.
*
*  @brief Definition for the Game Manager system
*
*  @section Description
*
*  Game Manager acts as the interface for the game state system. This will track the progress in the game and then behave accordingly.
*/

#pragma once

#include "pch.h"

#include "PlayerData.h"
#include "GameData.h"
#include "SceneState.h"

struct GameStateData;

class GameManager 
{
public:
	GameManager() = default;
	~GameManager() = default;

	void init();

	void tickGameManager(GameStateData* _GSD);

	void registerPlayer(Player2D*	new_player);
	void addWorldEventListener(std::shared_ptr<SceneEvent>	world_event_listener);
	
	std::vector<PlayerData> getPlayerDataArray() const; // TODO - Consider returning a refrence to the array instead. 
	void addPlayerData(PlayerData new_player_data);

	GameData getGameModeData() const;
	void	 setGameModeData(GameData new_game_data);

	// Game Manager Event Handlers.
	void setupGame();
	void startGame();
	void resetManager();

private:
	void checkPlayerLifeStatus();
	void checkPlayerRespawnStatus(float delta_time);

	bool shouldRespawnPlayer(Player2D* player);
	void respawnPlayer(Player2D* player);

	void updatePlayerScore();

	void endCurrentGame();

	std::vector<Player2D*>			level_players;
	std::vector<Player2D*>			players_to_respawn; /// < Buffer of players that need to be respawned.

	std::vector<PlayerData>			current_players;

	SceneState						world;
	GameData						game_mode;
	bool							game_active = false;
	bool							time_limit = true;

	float							game_time;
};