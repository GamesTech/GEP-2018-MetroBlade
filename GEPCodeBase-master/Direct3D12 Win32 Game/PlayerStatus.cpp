#include "pch.h"
#include "PlayerStatus.h"

void PlayerStatus::tickComponent(GameStateData * _GSD)
{
	return;
}

void PlayerStatus::renderComponent(RenderData * _RD)
{
	return;
}

int PlayerStatus::getLives() const
{
	return lives;
}

void PlayerStatus::setLives(int new_life_count)
{
	lives = new_life_count;
}

int PlayerStatus::getDamagePercentage() const
{
	return damage_percentage;
}

void PlayerStatus::setDamagePercentage(int new_damage_percentage)
{
	damage_percentage = new_damage_percentage;
}

int PlayerStatus::getScore() const
{
	return score;
}

void PlayerStatus::setScore(int new_score)
{
	score = new_score;
}

int PlayerStatus::getLaunchMultiplier() const
{
	return launch_multiplier;
}

void PlayerStatus::setLaunchMultiplier(int new_multiplier)
{
	launch_multiplier = new_multiplier;
}

void PlayerStatus::setHealth(int value)
{
	current_health = value;
}

void PlayerStatus::addHealth(int value_to_add)
{
	current_health += value_to_add;
}

void PlayerStatus::takeHealth(int value_to_subtract)
{
	current_health -= value_to_subtract;
}
