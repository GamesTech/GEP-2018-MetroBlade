#include "pch.h"
#include "UICanvas.h"

void UICanvas::addUIObject(UIObject * new_object)
{
	ui_objects.push_back(std::unique_ptr<UIObject>(new_object)); 
}
