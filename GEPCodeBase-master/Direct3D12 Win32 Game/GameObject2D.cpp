#include "pch.h"
#include "GameObject2D.h"


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
