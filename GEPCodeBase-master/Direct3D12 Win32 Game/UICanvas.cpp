#include "pch.h"
#include "RenderData.h"

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
	ID3D12DescriptorHeap* heaps[] = { _RD->m_resourceDescriptors->Heap() };
	_RD->m_commandList->SetDescriptorHeaps(_countof(heaps), heaps);
	_RD->m_spriteBatch->Begin(_RD->m_commandList.Get());
	for (auto& object : ui_objects) 
	{
		object->Render(_RD);
	}
	_RD->m_spriteBatch->End();
}

void UICanvas::addWorldEventListener(std::shared_ptr<SceneEvent> world_event_listener)
{
	event_listener = world_event_listener;
	world.assignSceneManagerListener(world_event_listener);
}

void UICanvas::clearUICanvas()
{
	ui_objects.clear();
}

