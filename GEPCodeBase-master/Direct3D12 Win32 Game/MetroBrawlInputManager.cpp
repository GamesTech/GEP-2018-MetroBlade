#include "pch.h"
#include "MetroBrawlInputManager.h"

void MetroBrawlInputManager::init(HWND& window)
{
	// Setup the input devices here. Also setup the bindings for each of the devices.
	mouse_input->SetWindow(window);
	mouse_input->SetMode(DirectX::Mouse::Mode::MODE_RELATIVE);
	loadBinds();

#ifdef ARCADE
	// Here we initialise the ARCADE controllers.
	arcade_controls.initModule("");
#endif
}

void MetroBrawlInputManager::tick()
{
	// Here we update the state of inputs in the binds.
	keyboard_state = keyboard_input->GetState();
	mouse_state = mouse_input->GetState();

#ifdef ARCADE 
	arcade_controls.tickDriver();
#endif

	updateControllerState();
	updateBindState();
	updateControllerBindState();
}

bool MetroBrawlInputManager::getKeyDown(DirectX::Keyboard::Keys key)
{
	return keyboard_input->GetState().IsKeyDown(key); // TODO - used updated state value.
}

bool MetroBrawlInputManager::getKeyUp(DirectX::Keyboard::Keys key)
{
	return keyboard_input->GetState().IsKeyUp(key); // TODO - used updated state value.
}

bool MetroBrawlInputManager::getMouseButtonDown(MetroBrawlInputActions mouse_button)
{
	bool isDown = false;

	switch (mouse_button) 
	{
	case MetroBrawlInputActions::KEY_MOUSE_LEFTBUTTON:
		{
			isDown = mouse_state.leftButton;
			break;
		}
		case MetroBrawlInputActions::KEY_MOUSE_RIGHTBUTTON:
		{
			isDown = mouse_state.rightButton;
			break;
		}
		case MetroBrawlInputActions::KEY_MOUSE_MIDDLEBUTTON:
		{
			isDown = mouse_state.middleButton;
			break;
		}
	}

	return isDown;
}

Vector2 MetroBrawlInputManager::getMouseCoordinates()
{
	return Vector2(mouse_input->GetState().x, mouse_input->GetState().y);
}

int MetroBrawlInputManager::getMouseScrollWheelValue() const
{
	return mouse_input->GetState().scrollWheelValue;
}

int MetroBrawlInputManager::getControllerKeyValue(MetroBrawlInputActions controller_button, int device_id)
{
	// Check button keys. Values can be cast according to data needs. 
	int key_value = 0;
	const int key_bind = ((int)controller_button - 259);

	int key_values[DEVICE_CONTROLLER_BUTTONS_COUNT] = // Map of the key values used to retrieve the correct number.
	{
		gamepad_state[device_id].state.buttons.a,
		gamepad_state[device_id].state.buttons.b,
		gamepad_state[device_id].state.buttons.x,
		gamepad_state[device_id].state.buttons.y,
		gamepad_state[device_id].state.dpad.up,
		gamepad_state[device_id].state.dpad.down,
		gamepad_state[device_id].state.dpad.left,
		gamepad_state[device_id].state.dpad.right,
		gamepad_state[device_id].state.buttons.start,
		gamepad_state[device_id].state.buttons.back,
		gamepad_state[device_id].state.thumbSticks.leftX,
		gamepad_state[device_id].state.thumbSticks.leftY,
		gamepad_state[device_id].state.thumbSticks.rightX,
		gamepad_state[device_id].state.thumbSticks.rightY,
		gamepad_state[device_id].state.buttons.leftShoulder,
		gamepad_state[device_id].state.buttons.rightShoulder
	};
	
	key_value = key_values[key_bind];

	return key_value;
}

bool MetroBrawlInputManager::getBindDown(std::string bind)
{
	int  isDown = 0;
	InputBind* bind_ptr = nullptr;
	bind_ptr = findBind(bind);

	// Checks both controllers and Keyboard to see if key is down.
	if (bind_ptr) 
	{
		isDown = bind_ptr->input_value;
	}

	for (int i = 0; i < gamepad_state.size(); i++) 
	{
		bind_ptr = findControllerBind(bind, i);
		if (bind_ptr)
		{
			isDown |= abs(bind_ptr->input_value);
		}

		if (isDown) break;
	}

	return (bool)isDown;
}

void MetroBrawlInputManager::updateControllerState()
{
	for (int i = 0; i < DirectX::GamePad::MAX_PLAYER_COUNT; i++)
	{
#ifdef ARCADE
		if (i < DEVICE_CONTROLLER_COUNT_ARCADE)
		{
			gamepad_state[i].state = arcade_controls.getControllerState(i);
		}
		else 
		{
			gamepad_state[i].state = gamepad_input->GetState(i);
		}
#else
		gamepad_state[i].state = gamepad_input->GetState(i);
#endif
	}
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
			
			for (auto& key : bind.value().array_range()) 
			{
				new_bind.key_identifier = ((MetroBrawlInputActions)key.as_int());

				if (new_bind.key_identifier >= (int)MetroBrawlInputActions::KEY_CONTROLLER_A)
				{
					loadControllerBinds(new_bind);
				}
				else 
				{
					action_binds.push_back(new_bind);
				}
			}
		}
	}
}

void MetroBrawlInputManager::loadControllerBinds(InputBind& new_bind)
{
	for (int controller = 0; controller < gamepad_state.size(); controller++) 
	{
		new_bind.device_id = controller;
		gamepad_state[controller].binds.push_back(new_bind); // Place the bind on the controller.
	}
}

void MetroBrawlInputManager::updateBindState()
{
	// Update state information for every type of bind.
	for (auto& bind_entity : action_binds)
    {
		bind_entity.prev_input_value = bind_entity.input_value;

		if (bind_entity.key_identifier <= MAX_KEY_SWITCH_VALUE)
		{
			// Key State so value returned should be a bool. 
			getBindButtonValue(bind_entity);
		}
		else 
		{
			// Its a mouse wheel.
			bind_entity.input_value = mouse_state.scrollWheelValue;
		}
	}
}

void MetroBrawlInputManager::updateControllerBindState()
{
	for (auto& controller : gamepad_state) 
	{
		// Only Update controller state if the controller is connected.
		if (controller.state.IsConnected()) 
		{
			for (auto& bind : controller.binds)
			{
				bind.prev_input_value = bind.input_value;
				bind.input_value = getControllerKeyValue(bind.key_identifier, bind.device_id);
			}
		}
	}
}

void MetroBrawlInputManager::getBindButtonValue(InputBind& value)
{
	if (value.key_identifier <= 0xfe) 
	{
		value.input_value = (int)keyboard_state.IsKeyDown((DirectX::Keyboard::Keys)value.key_identifier);
	}
	else 
	{
		// Its a mouse button.
		value.input_value = (int)getMouseButtonDown((MetroBrawlInputActions)value.key_identifier);
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

InputBind* MetroBrawlInputManager::findControllerBind(std::string bind)
{
	// Check the controllers next.
	for (auto& controller : gamepad_state)
	{
		if (controller.state.IsConnected())
		{
			for (auto& bind_entity : controller.binds)
			{
				if (bind_entity.binding_name == bind)
				{
					return &bind_entity;
				}
			}
		}
	}

	return nullptr;
}

InputBind* MetroBrawlInputManager::findControllerBind(std::string bind, int device_id)
{
	if (gamepad_state[device_id].state.IsConnected())
	{
		for (auto& bind_entity : gamepad_state[device_id].binds)
		{
			if (bind_entity.binding_name == bind)
			{
				return &bind_entity;
			}
		}
	}

	return nullptr;
}
