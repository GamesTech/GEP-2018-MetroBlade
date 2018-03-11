#include "pch.h"
#include "GameManager.h"
#include "GameStateData.h"
#include "Player2D.h"
#include "PlayerStatus.h"

constexpr int MAX_PLAYERS = 8;

void GameManager::init()
{
	level_players.reserve(MAX_PLAYERS);
	current_players.reserve(MAX_PLAYERS);
}

void GameManager::tickGameManager(GameStateData* _GSD)
{
	if ((!level_players.empty()) && game_active) 
	{
		// Here we check the state of the game. 
	}
}

void GameManager::registerPlayer(Player2D* new_player)
{
	// Setup player stats according to game mode and then register the player for checking every frame.
	new_player->getComponentManager()->getComponentByType<PlayerStatus>()->setLives(3);
	new_player->getComponentManager()->getComponentByType<PlayerStatus>()->setDamagePercentage(0);
	new_player->getComponentManager()->getComponentByType<PlayerStatus>()->setScore(0);
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

void GameManager::startGame()
{
	game_active = true;
}

void GameManager::endCurrentGame()
{
	world.changeScene("gm_results_screen");
}
