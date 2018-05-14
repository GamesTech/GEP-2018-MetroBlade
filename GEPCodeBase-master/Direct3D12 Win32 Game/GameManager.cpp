#include "pch.h"

#include <random>

#include "GameManager.h"
#include "GameStateData.h"

#include "Player2D.h"
#include "SpawnPoint.h"

#include "PlayerStatus.h"
#include "LobbySystem.h"

constexpr int MAX_PLAYERS = 8;

void GameManager::init()
{
	player_instances.reserve(MAX_PLAYERS);
	lobby.reserve(MAX_PLAYERS);
	players_to_respawn.reserve(MAX_PLAYERS);
}

void GameManager::tickGameManager(GameStateData* _GSD)
{
	if ((!player_instances.empty()) && game_active) 
	{
		// Here we check the state of the game. 
		if (game_mode.game_length != GAME_INFINITE_TIME)
		{
			// Tick time and if it reaches 0 then end the game. 
			game_mode_state.game_length -= _GSD->m_dt;
			if (game_mode_state.game_length <= 0)
			{
				// TODO - Add code to change level to the results screen
				endCurrentGame();
				OutputDebugString(L"The Games Ended Mate \n");
				return; 
			}
		}

		// check for lives of the players. 
		checkPlayerLifeStatus();
		checkPlayerRespawnStatus(_GSD->m_dt);
	}
}

void GameManager::registerPlayerInstance(GameObject2D * new_player)
{
	// Setup player stats according to game mode and then register the player for checking every frame.
	// TODO - Move [layer setup to when the game starts. 
	if (dynamic_cast<Player2D*>(new_player)) 
	{
		new_player->getComponentManager()->getComponentByType<LobbySystemComponent>()->addLobbyReference(&lobby);
		player_instances.push_back((Player2D*)new_player);
	}
}

void GameManager::setupLobbySystemComponent(GameObject2D* object)
{
	LobbySystemComponent* component = object->getComponentManager()->getComponentByType<LobbySystemComponent>();

	if (component) 
	{
		component->addLobbyRefrence(this);
	}
}

void GameManager::addWorldEventListener(std::shared_ptr<SceneEvent> world_event_listener)
{
	world.assignSceneManagerListener(world_event_listener);
}

std::vector<PlayerData>* GameManager::getPlayerLobbyData()
{
	return &lobby;
}

std::vector<SpawnPoint*>* GameManager::getSpawnpointList()
{
	return &scene_spawns;
}

PlayerStatus* GameManager::getPlayerInstanceStatus(int index)
{
	PlayerStatus*  status = nullptr;
	
	if (index < player_instances.size()) 
	{
		status = player_instances[index]->getComponentManager()->getComponentByType<PlayerStatus>();
	}

	return status;
}

void GameManager::addPlayer(PlayerData new_player_data) // TODO - Consider Removing.
{
	lobby.push_back(new_player_data);
}

GameData* GameManager::getGameModeData()
{
	return &game_mode;
}

GameData* GameManager::getGameModeStatus()
{
	return &game_mode_state;
}

void GameManager::setupGame()
{
	for (auto& player : player_instances) 
	{
		player->getComponentManager()->getComponentByType<PlayerStatus>()->setLaunchMultiplier(game_mode.game_knockback_multiplier);
		player->getComponentManager()->getComponentByType<PlayerStatus>()->setLives(game_mode.number_of_lives);
		player->getComponentManager()->getComponentByType<PlayerStatus>()->setDamagePercentage(0);
	}

	game_mode_state = game_mode;
}

void GameManager::startGame()
{
	game_active = true;
}

void GameManager::resetManager()
{
	game_active = false;
	player_instances.clear();
	scene_spawns.clear();
}

void GameManager::setUILabel(UILabel * new_label)
{
	timer_label = new_label;
}

void GameManager::registerSpawnPoint(GameObject2D* spawn_point_object)
{
	SpawnPoint* new_point = dynamic_cast<SpawnPoint*>(spawn_point_object);

	if (new_point) 
	{
		scene_spawns.push_back(new_point);
	}
}

Vector2 GameManager::getRespawnPosition()
{
	int size = scene_spawns.size() - 1;

	if ((size + 1) != 0) 
	{
		std::random_device  rd{};
		std::mt19937  generator(rd());
		std::uniform_int_distribution<int>  rng{ 0, size };
		return scene_spawns[rng(generator)]->GetPos();
	}
	else 
	{
		return Vector2(10, 10);
	}
}

void GameManager::checkPlayerLifeStatus()
{
	for (auto& player : player_instances)
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
			players_to_respawn[i]->SetPos(getRespawnPosition()); // TODO - Add code to respawn the player.
			players_to_respawn.erase(players_to_respawn.begin() + i);
			OutputDebugString(L"Ive Respawned Mate");
		}
	}
}

bool GameManager::shouldRespawnPlayer(Player2D* player)
{
	bool return_val = false;

	// Is the player in the list.a
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
	// TODO - Consider making component/event driven. As score changes may very.
}

void GameManager::endCurrentGame()
{
	// TODO - Add links to a results screen based on the player data aquired from the last game.
	for (int i = 0; i < lobby.size(); ++i) 
	{
		// Sets the Player Data which can then be displayed for players to view.
		lobby[i].player_data = *(player_instances[i]->getComponentManager()->getComponentByType<PlayerStatus>());
	}

	world.changeScene("clear");
}
