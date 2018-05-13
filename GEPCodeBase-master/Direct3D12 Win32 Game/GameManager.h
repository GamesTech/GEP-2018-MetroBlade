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

class UILabel;
class SpawnPoint;

struct GameStateData;


class GameManager 
{
public:
	GameManager() = default;
	~GameManager() = default;

	void init();

	void tickGameManager(GameStateData* _GSD);

	void registerPlayerInstance(GameObject2D * new_player);
	void setupLobbySystemComponent(GameObject2D*  object);
	void addWorldEventListener(std::shared_ptr<SceneEvent>	world_event_listener);
	
	std::vector<PlayerData>* getPlayerLobbyData(); // TODO - Consider returning a refrence to the array instead. 
	std::vector<SpawnPoint*>*  getSpawnpointList(); 
	void addPlayer(PlayerData new_player_data);

	GameData* getGameModeData();
	GameData* getGameModeStatus();

	// Game Manager Event Handlers.
	void setupGame();
	void startGame();
	void resetManager();

	void setUILabel(UILabel* new_label);

	void registerSpawnPoint(GameObject2D*  spawn_point_object);

private:
	// TODO - Add Spawnpoint register for determining locations hwne respawning players.
	Vector2 getRespawnPosition(); 

	void checkPlayerLifeStatus();
	void checkPlayerRespawnStatus(float delta_time);

	bool shouldRespawnPlayer(Player2D* player);
	void respawnPlayer(Player2D* player);

	void updatePlayerScore();

	void endCurrentGame();

	std::vector<Player2D*>			player_instances;
	std::vector<Player2D*>			players_to_respawn; /// < Buffer of players that need to be respawned.
	std::vector<SpawnPoint*>		scene_spawns;

	std::vector<PlayerData>			lobby;

	SceneState						world;
	GameData						game_mode;
	GameData						game_mode_state; ///< The present game state which is passed trough to objects. 

	bool							game_active = false;
	float							game_time;

	UILabel*						timer_label = nullptr;
};