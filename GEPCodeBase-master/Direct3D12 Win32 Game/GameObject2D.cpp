#include "pch.h"
#include "GameObject2D.h"
#include "GameComponentManager.h"


GameObject2D::GameObject2D()
{
}


GameObject2D::~GameObject2D()
{
}

void GameObject2D::assignWorldEventListener(std::shared_ptr<SceneEvent> world_event_listener)
{
	world.assignSceneManagerListener(world_event_listener);
}

GameComponentManager* GameObject2D::getComponentManager()
{
	return &object_components;
}

void GameObject2D::assignSceneManager(SceneManager* manager)
{
	world.assignSceneManager(manager);
}

