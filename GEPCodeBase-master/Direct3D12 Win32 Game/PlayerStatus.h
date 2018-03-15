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

private: 
	int lives = -1;
	int damage_percentage = 0;
	int score = 0;
};