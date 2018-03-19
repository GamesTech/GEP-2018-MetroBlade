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
	players_to_respawn.reserve(MAX_PLAYERS);
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
				// TODO - Add code to change level to the results screen
				endCurrentGame();
				OutputDebugString(L"The Games Ended Mate \n");
			}
		}

		// check for lives of the players. 
		checkPlayerLifeStatus();
		checkPlayerRespawnStatus(_GSD->m_dt);
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
		player->getComponentManager()->getComponentByType<PlayerStatus>()->setLaunchMultiplier(game_mode.game_knockback_multiplier);
		player->getComponentManager()->getComponentByType<PlayerStatus>()->setLives(game_mode.number_of_lives);
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
	for (auto& player : level_players)
	{
		if (player->isDead()) 
		{
			if (shouldRespawnPlayer(player)) 
			{
				respawnPlayer(player);
				// Here we add them to a respawn list if there not being respawned.
				OutputDebugString(L"Im going to respawn mate \n");
			}

			// change the score accordingly.
			OutputDebugString(L"Im dead mate \n");
		}
	}
}

void GameManager::checkPlayerRespawnStatus(float delta_time)
{
	float new_time;
	for (int i = 0; i < players_to_respawn.size(); i++) 
	{
		new_time = players_to_respawn[i]->getRespawnTime();
		new_time -= delta_time;
		players_to_respawn[i]->setRespawnTime(new_time);

		if (new_time <= 0)
		{
			players_to_respawn[i]->setRespawnTime(0.0f);
			players_to_respawn[i]->isDead(false);
			players_to_respawn[i]->SetPos(Vector2(800, 500)); // TODO - Add code to respawn the player.
			players_to_respawn.erase(players_to_respawn.begin() + i);
			OutputDebugString(L"Ive Respawned Mate");
		}
	}
}

bool GameManager::shouldRespawnPlayer(Player2D* player)
{
	bool return_val = false;

	// Is the player in the list.
	for (auto& respawnable_player : players_to_respawn)
	{
		if (respawnable_player == player)
		{
			return false;
		}
	}

	if (game_mode.number_of_lives != GAME_INFINITE_LIVES)
	{
		PlayerStatus*  player_stats = player->getComponentManager()->getComponentByType<PlayerStatus>();

		if (player_stats->getLives() != 0)
		{
			player_stats->setLives(player_stats->getLives() - 1);

			if (player_stats->getLives() != 0)
			{
				return_val = true;
			}
		}
	}
	else 
	{
		return_val = true;
	}

	return return_val;
}

void GameManager::respawnPlayer(Player2D* player)
{
	// Add the player to the respawn list and respawn them.
	player->setRespawnTime(game_mode.respawn_time);
	players_to_respawn.push_back(player);
}

void GameManager::updatePlayerScore()
{
	// TODO - Add code to update the players score according to game mode variables.

}

void GameManager::endCurrentGame()
{
	world.changeScene("clear");
}
