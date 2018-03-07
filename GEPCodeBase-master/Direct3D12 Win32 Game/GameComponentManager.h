/**
*  @file    GameComponentManager.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    07/03/2018
*  @version v1.0
*
*  @section System Module
*           Component System Module.
*
*  @brief Defines interface for controlling game components.
*
*  @section Description
*
*  The Game Component Manager functions as a container for all game components in the engine.
*/

#pragma once

#include "GameComponent.h"

class GameComponentManager 
{
public:
	GameComponentManager() = default;
	~GameComponentManager() = default;

	void addComponent(GameComponent*  new_component);

	// Component Manager Utilities
	template<class T>
	T*					getComponentByType();
	template<class T>
	std::vector<T*>		getComponentsByType();
	GameComponent*		getComponentByTag(std::string  tag);

private:
	std::vector<std::unique_ptr<GameComponent>>  component_list;
};

template<class T>
inline T* GameComponentManager::getComponentByType()
{
	T*		return_component = nullptr;

	for (auto& component : component_list) 
	{
		return_component = dynamic_cast<T*>(component);
		if (return_component) 
		{
			break;
		}
	}

	return return_component;
}

template<class T>
inline std::vector<T*> GameComponentManager::getComponentsByType()
{
	std::vector<T*>		object_components;
	T*				    component_refrence = nullptr;
	object_components.reserve(10);

	for (auto& component : component_list) 
	{
		component_refrence = dynamic_cast<T*>(component);
		if (component_refrence) 
		{
			object_components.push_back(component_refrence);
			component_refrence = nullptr;
		}
	}

	return object_components;
}
