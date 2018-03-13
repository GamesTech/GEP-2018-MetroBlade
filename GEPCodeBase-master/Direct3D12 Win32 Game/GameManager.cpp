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
		if (game_mode.game_length != GAME_INFINITE_TIME)
		{
			// Tick time and if it reaches 0 then end the game. 
			game_time -= _GSD->m_dt;
			if (game_time <= 0)
			{
				OutputDebugString(L"The Games Ended Mate \n");
			}
		}

		// check for lives of the players. 
		checkPlayerLifeStatus();
	}
}

void GameManager::registerPlayer(Player2D* new_player)
{
	// Setup player stats according to game mode and then register the player for checking every frame.
	// TODO - Move [layer setup to when the game starts. 
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

void GameManager::setupGame()
{
	for (auto& player : level_players) 
	{
		player->getComponentManager()->getComponentByType<PlayerStatus>()->setLives(3);
		player->getComponentManager()->getComponentByType<PlayerStatus>()->setDamagePercentage(0);
	}
	game_time = game_mode.game_length;
}

void GameManager::startGame()
{
	game_active = true;
}

void GameManager::resetManager()
{
	level_players.clear();
}

void GameManager::checkPlayerLifeStatus()
{
	if (game_mode.number_of_lives != GAME_INFINITE_LIVES) 
	{
		for (auto& player : level_players)
		{
			if (player->isDead()) 
			{
				// change the score accordingly.
				OutputDebugString(L"Im dead mate \n");
			}
		}
	}
}

void GameManager::endCurrentGame()
{
	world.changeScene("gm_results");
}
