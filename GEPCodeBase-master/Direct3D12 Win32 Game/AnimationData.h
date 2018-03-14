#pragma once

#include "pch.h"

struct AnimationData 
{
	std::string				 anim_state_name = "null_state";
	float					 time_step = 0.0f;
	std::vector<RECT>		 sprite_frames;
};