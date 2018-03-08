#pragma once
#include <string>
#include <vector>
#include <windef.h>
struct AnimationData
{
	std::string anim_name;
	std::vector<RECT> anim_rect;
};