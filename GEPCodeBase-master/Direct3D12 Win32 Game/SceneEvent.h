#pragma once

#include <string>

#include "GameEvent.h"

enum SceneEventFlags 
{
	EVENT_SIGNONE = 0,
	EVENT_SIGPAUSE,
	EVENT_SIGCHANGE,
	EVENT_SIGINSTANCIATE,
	EVENT_SIGEXIT,
	EVENT_SIGKILL
};

struct SceneEvent : public GameEvent 
{
	SceneEventFlags		event_flag = EVENT_SIGNONE;
	std::string			new_map    = "clear";
};