/**
*  @file    PlayerStatus.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    11/03/2018
*  @version v1.0
*
*  @section System Module
*           GamePlay
*
*  @brief Definition for Player Stats Data Container
*
*  @section Description
*
*  Set of classes and templates that are risponcable for holding on to the players stats like there health and movement speed,
*  score etc.
*/


#pragma once

#include "GameComponent.h"
#include "GameData.h"

class PlayerStatus : public GameComponent 
{
public:
	PlayerStatus() = default;
	~PlayerStatus() = default;

	// Inherited via GameComponent
	void tickComponent(GameStateData * _GSD) override;
	void renderComponent(RenderData * _RD) override;
	
	// Status interface
	int getLives() const;
	void setLives(int new_life_count);
	int getDamagePercentage() const;
	void setDamagePercentage(int new_damage_percentage);
	int getScore() const;
	void setScore(int new_score);
	int getLaunchMultiplier() const;
	void setLaunchMultiplier(int new_multiplier);
	int getHealth() { return current_health; }
	void setHealth(int value);
	void addHealth(int value_to_add);
	void takeHealth(int value_to_subtract);
private: 

	// TODO - Consider using an array for these variables.
	int lives = GAME_INFINITE_LIVES;
	int damage_percentage = 0;
	int score = 0;
	int launch_multiplier = 1;
	const int max_health = 100;
	int current_health = max_health;
};