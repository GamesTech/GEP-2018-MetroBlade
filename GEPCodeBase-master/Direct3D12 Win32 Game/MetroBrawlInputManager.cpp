#include "pch.h"
#include "MetroBrawlInputManager.h"

void MetroBrawlInputManager::init(HWND& window)
{
	// Setup the input devices here. Also setup the bindings for each of the devices.
	mouse_input->SetWindow(window);
	mouse_input->SetMode(DirectX::Mouse::Mode::MODE_RELATIVE);
	loadBinds();
}

void MetroBrawlInputManager::tick()
{
	// Here we update the state of inputs in the binds.
	keyboard_state = keyboard_input->GetState();
	mouse_state = mouse_input->GetState();

	for (int i = 0; i < DirectX::GamePad::MAX_PLAYER_COUNT; i++) 
	{
		gamepad_state[i] = gamepad_input->GetState(i);
	}

	updateBindState();
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
	return true;
}

Vector2 MetroBrawlInputManager::getMouseCoordinates()
{
	return Vector2(mouse_input->GetState().x, mouse_input->GetState().y);
}

int MetroBrawlInputManager::getMouseScrollWheelValue() const
{
	return mouse_input->GetState().scrollWheelValue;
}

bool MetroBrawlInputManager::getBindDown(std::string bind)
{
	return ((bool)findBind(bind)->input_value);
}

void MetroBrawlInputManager::loadBinds()
{
	action_binds.reserve(100);
	input_bind_file.setFilePath("binds.mbconfig");
	if (input_bind_file.parseFile()) 
	{
		InputBind   new_bind;
		for (auto& bind : input_bind_file.getFileBuffer().members()) 
		{
			new_bind.binding_name = bind.name();
			new_bind.key_identifier = ((MetroBrawlInputKeyBindings)bind.value().as_int());
			action_binds.push_back(new_bind);
		}
	}
}

void MetroBrawlInputManager::updateBindState()
{
	// Update state information for every type of bind.
	for (auto& bind_entity : action_binds)
    {
		if (bind_entity.key_identifier <= MAX_KEYBOARD_VALUE) 
		{
			// Key State so value returned should be a bool. 
			bind_entity.input_value = (int)keyboard_state.IsKeyDown((DirectX::Keyboard::Keys)bind_entity.key_identifier);
		}
	}
}

InputBind* MetroBrawlInputManager::findBind(std::string bind)
{
	for (auto& bind_entity : action_binds) 
	{
		if (bind_entity.binding_name == bind) 
		{
			return &bind_entity;
		}
	}

	return nullptr;
}
