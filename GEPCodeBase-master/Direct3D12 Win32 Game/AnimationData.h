/**
*  @file    AnimationData.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    14/03/2018
*  @version v1.0
*
*  @section System Module
*           Gameplay Management.
*
*  @brief Definition for the AnimationData structure
*
*  @section Description
*
*  Defines all animation frames within a spritesheet as well as timing data for animation playback. 
*/


#pragma once

#include "pch.h"

struct AnimationData 
{
	std::string				 anim_state_name = "null_state";
	float					 time_step = 0.0f;
	std::vector<RECT>		 anim_frames;
};