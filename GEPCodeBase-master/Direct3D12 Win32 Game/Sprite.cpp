#include "Sprite.h"
#include "pch.h"
#include "GameStateData.h"

Sprite::Sprite(bool animated)
{
	is_animated = animated;

	//testing animation data structure
	idle_anim_data.reset(new AnimationData);
	idle_anim_data->anim_name = "Idle";
	idle_anim_data->anim_rect.resize(2);
	
	idle_anim_data->anim_rect[0].left = 0;
	idle_anim_data->anim_rect[0].top = 0;
	idle_anim_data->anim_rect[0].right = 100;
	idle_anim_data->anim_rect[0].bottom = 126;

	idle_anim_data->anim_rect[1].left = 100;
	idle_anim_data->anim_rect[1].top = 0;
	idle_anim_data->anim_rect[1].right = 199;
	idle_anim_data->anim_rect[1].bottom = 126;
	
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
	anim_time += _GSD->m_dt;
	switch (current_anim)
	{
	case IDLE_ANIM:

		if (anim_time < 0.5f)
		{
			TestFunc(idle_anim_data->anim_rect[0]);
		}
		else if (anim_time > 0.5f && anim_time < 1.0f)
		{
			TestFunc(idle_anim_data->anim_rect[1]);
		}
		else if (anim_time > 1.0f)
		{
			anim_time = 0.0f;
		}

		break;
	case MOVE_ANIM:
		if (anim_time < 0.25f)
		{
			ChangeRectPos(442, 0, 536, 126);
		}
		else if (anim_time > 0.0f && anim_time < 0.2f)
		{
			ChangeRectPos(536, 0, 630, 126);
		}
		else if (anim_time > 0.2f && anim_time < 0.4f)
		{
			ChangeRectPos(630, 0, 724, 126);
		}
		else if (anim_time > 0.4f && anim_time < 0.6f)
		{
			ChangeRectPos(724, 0, 818, 126);
		}
		else if (anim_time > 0.6f && anim_time < 0.8f)
		{
			ChangeRectPos(630, 0, 724, 126);
		}
		else if (anim_time > 0.8f && anim_time < 1.0f)
		{
			ChangeRectPos(536, 0, 630, 126);
		}
		else if (anim_time > 1.0f && anim_time < 1.2f)
		{
			ChangeRectPos(442, 0, 536, 126);
		}
		else if (anim_time > 1.2f)
		{
			anim_time = 0.0f;
		}
		break;
	case JUMP_ANIM:
		ChangeRectPos(1006, 0, 1101, 126);
		anim_time = 0.0f;
		break;
	case ATTACK_ANIM:
		break;
	}
};