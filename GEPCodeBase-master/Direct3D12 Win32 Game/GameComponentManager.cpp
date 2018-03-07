#include "pch.h"
#include "GameComponentManager.h"

void GameComponentManager::addComponent(GameComponent* new_component)
{
	component_list.push_back(std::unique_ptr<GameComponent>(new_component));
}

GameComponent* GameComponentManager::getComponentByTag(std::string tag)
{
	GameComponent*		return_component = nullptr;

	for (auto& component : component_list) 
	{
		if (component->getTag() == tag) 
		{
			return_component = component.get();
			break;
		}
	}

	return return_component;
}
