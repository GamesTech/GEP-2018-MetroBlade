#include "pch.h"
#include "WorldEvent.h"

#include "Scene.h"
#include "GameObject2D.h"

WorldEvent::WorldEvent(Scene* listening_scene)
{
	current_scene = listening_scene;
}

void WorldEvent::changeScene()
{
	current_scene->clearScene();
}

void WorldEvent::spawn2DObject(GameObject2D* new_object)
{
	current_scene->add2DGameObjectToScene(new_object);
}
