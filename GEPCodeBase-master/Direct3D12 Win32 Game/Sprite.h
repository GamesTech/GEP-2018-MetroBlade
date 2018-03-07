#pragma once
#include "ImageGO2D.h"

enum animation
{
	IDLE_ANIM,
	MOVE_ANIM,
	JUMP_ANIM,
	ATTACK_ANIM
};
class Sprite
{
public:
	
	Sprite(bool animated);
	~Sprite() = default;
	void ChangeRectPos(int pos1, int pos2, int pos3, int pos4);
	void PlayAnimation(GameStateData* _GSD);
	void SetRECT(std::shared_ptr<RECT> rect) { sprite_src_rect = rect; }
	void SetAnimation(animation new_animation) { current_anim = new_animation; }
private:
	bool is_animated = false;
	animation current_anim = IDLE_ANIM;
	float anim_time = 0.0f;
	std::shared_ptr<RECT>   sprite_src_rect;
};