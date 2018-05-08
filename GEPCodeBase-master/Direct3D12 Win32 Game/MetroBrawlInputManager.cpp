#include "pch.h"
#include "MetroBrawlInputManager.h"

void MetroBrawlInputManager::init(HWND& window)
{
	// Setup the input devices here. Also setup the bindings for each of the devices.
	mouse_input->SetWindow(window);
	mouse_input->SetMode(DirectX::Mouse::Mode::MODE_RELATIVE);
}

void MetroBrawlInputManager::tick()
{
	// Here we update the state of inputs in the binds.
}

bool MetroBrawlInputManager::getKeyDown(DirectX::Keyboard::Keys key)
{
	return keyboard_input->GetState().IsKeyDown(key);
}

bool MetroBrawlInputManager::getKeyUp(DirectX::Keyboard::Keys key)
{
	return keyboard_input->GetState().IsKeyUp(key);
}

bool MetroBrawlInputManager::getMouseButtonDown()
{
	return false;
}

Vector2 MetroBrawlInputManager::getMouseCoordinates()
{
	return Vector2(mouse_input->GetState().x, mouse_input->GetState().y);
}

int MetroBrawlInputManager::getMouseScrollWheelValue() const
{
	return mouse_input->GetState().scrollWheelValue;
}
