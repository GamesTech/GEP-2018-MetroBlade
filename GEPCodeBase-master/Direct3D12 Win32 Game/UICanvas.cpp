#include "pch.h"
#include "UICanvas.h"

void UICanvas::addUIObject(UIObject * new_object)
{
	new_object->assignWorldEventListener(event_listener);
	ui_objects.push_back(std::unique_ptr<UIObject>(new_object)); 
}

void UICanvas::tickUIObjects(GameStateData * _GSD)
{
	for (auto& object : ui_objects) 
	{
		object->Tick(_GSD);
	}
}

void UICanvas::renderUIObjects(RenderData * _RD)
{
	for (auto& object : ui_objects) 
	{
		object->Render(_RD);
	}
}

void UICanvas::addWorldEventListener(std::shared_ptr<SceneEvent> world_event_listener)
{
	event_listener = world_event_listener;
	world.assignSceneManagerListener(world_event_listener);
}

