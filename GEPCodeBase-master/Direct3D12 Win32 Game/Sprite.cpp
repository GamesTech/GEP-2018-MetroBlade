#include "Sprite.h"
#include "pch.h"
#include "GameStateData.h"
#include "SpriteAnimFileReader.h"

#include "FileExtenstionNames.h"


Sprite::Sprite(bool animated)
{
	is_animated = animated; // TODO - Consider reviewing this.
	//testing animation data structure
}

void Sprite::tickComponent(GameStateData* _GSD)
{
	total_time += _GSD->m_dt;

	if (total_time >= current_anim_state.time_step) 
	{
		if (frame_index + 1 > current_anim_state.anim_frames.size() - 1) 
		{
			if (loop) { frame_index = 0; }
		}
		else 
		{
			frame_index++;
		}

		total_time = 0.0f;
	}

	setAnimationFrame(current_anim_state.anim_frames[frame_index]); // Set the rectangle.
}

void Sprite::renderComponent(RenderData * _RD)
{
	// TODO - draw sprite based on the frame information.
	return;
}

void Sprite::setAnimationFrame(RECT new_rect)
{
	*sprite_src_rect = new_rect;
}

void Sprite::setAnimationState(std::string new_animation_state)
{
	for (auto& anim_state : anim_vector) 
	{
		if ((anim_state.anim_state_name == new_animation_state)
			&& (current_anim_state.anim_state_name != new_animation_state)) 
		{
				current_anim_state = anim_state;
				frame_index = 0;
		}
	}
}

void Sprite::setSpriteAnimationFile(std::string file_name)
{
	SpriteAnimFileReader   file_reader;
#ifdef _DEBUG
	file_reader.setFileName("..\\Images\\" + file_name + FILE_ANIMATION_EXTENSTION);
#else
#endif
	assert(!file_reader.parseFile(anim_vector));
}

void Sprite::setLoop(bool loop_value)
{
	loop = loop_value;
}
