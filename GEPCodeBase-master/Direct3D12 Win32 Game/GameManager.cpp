#include "pch.h"
#include "GameManager.h"
#include "GameStateData.h"

constexpr int MAX_PLAYERS = 8;

void GameManager::init()
{
	level_players.reserve(MAX_PLAYERS);
	current_players.reserve(MAX_PLAYERS);
}

void GameManager::tickGameManager(GameStateData* _GSD)
{
	if (!level_players.empty()) 
	{
		// Here we check the state of the game. 
	}

	// Do Stuff Here. 
}

void GameManager::registerPlayer(Player2D* new_player)
{
	level_players.push_back(new_player);
}

void GameManager::addWorldEventListener(std::shared_ptr<SceneEvent> world_event_listener)
{
	world.assignSceneManagerListener(world_event_listener);
}

std::vector<PlayerData> GameManager::getPlayerDataArray() const
{
	return current_players;
}

void GameManager::addPlayerData(PlayerData new_player_data)
{
	current_players.push_back(new_player_data);
}

GameData GameManager::getGameModeData() const
{
	return game_mode;
}

void GameManager::setGameModeData(GameData new_game_data)
{
	game_mode = new_game_data;
}

void GameManager::endCurrentGame()
{
	world.changeScene("gm_results_screen");
}
