#include "Sprite.h"
#include "pch.h"
#include "GameStateData.h"

Sprite::Sprite(bool animated)
{
	is_animated = animated;

	//testing animation data structure

	anim_vector.resize(1);
	anim_vector[0].anim_name = "Idle";
	anim_vector[0].anim_rect.resize(2);

	anim_vector[0].interval_time = 0.5f;
	anim_vector[0].anim_rect[0].left = 0;
	anim_vector[0].anim_rect[0].top = 0;
	anim_vector[0].anim_rect[0].right = 100;
	anim_vector[0].anim_rect[0].bottom = 126;

	anim_vector[0].anim_rect[1].left = 100;
	anim_vector[0].anim_rect[1].top = 0;
	anim_vector[0].anim_rect[1].right = 199;
	anim_vector[0].anim_rect[1].bottom = 126;

	
}

void Sprite::ChangeRectPos(int pos1, int pos2, int pos3, int pos4)
{
	sprite_src_rect->left = pos1;
	sprite_src_rect->top = pos2;
	sprite_src_rect->right = pos3;
	sprite_src_rect->bottom = pos4;
}

void Sprite::TestFunc(RECT new_rect)
{
	*sprite_src_rect = new_rect;
}

void Sprite::PlayAnimation(GameStateData* _GSD)
{
	
	total_time += _GSD->m_dt;

	float anim_time = 0;
	switch (current_anim)
	{
	case IDLE_ANIM:
		anim_time = anim_vector[0].interval_time;
		if (total_time < anim_time)
		{
			TestFunc(anim_vector[0].anim_rect[0]);
		}
		else if (total_time > anim_time && total_time < 1.0f)
		{
			TestFunc(anim_vector[0].anim_rect[1]);
		}
		else if (total_time > 1.0f)
		{
			total_time = 0.0f;
		}

		break;
	case MOVE_ANIM:
		if (total_time < 0.25f)
		{
			ChangeRectPos(442, 0, 536, 126);
		}
		else if (total_time > 0.0f && total_time < 0.2f)
		{
			ChangeRectPos(536, 0, 630, 126);
		}
		else if (total_time > 0.2f && total_time < 0.4f)
		{
			ChangeRectPos(630, 0, 724, 126);
		}
		else if (total_time > 0.4f && total_time < 0.6f)
		{
			ChangeRectPos(724, 0, 818, 126);
		}
		else if (total_time > 0.6f && total_time < 0.8f)
		{
			ChangeRectPos(630, 0, 724, 126);
		}
		else if (total_time > 0.8f && total_time < 1.0f)
		{
			ChangeRectPos(536, 0, 630, 126);
		}
		else if (total_time > 1.0f && total_time < 1.2f)
		{
			ChangeRectPos(442, 0, 536, 126);
		}
		else if (total_time > 1.2f)
		{
			total_time = 0.0f;
		}
		break;
	case JUMP_ANIM:
		ChangeRectPos(1006, 0, 1101, 126);
		total_time = 0.0f;
		break;
	case ATTACK_ANIM:
		break;
	}
};