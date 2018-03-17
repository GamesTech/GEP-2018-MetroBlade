#pragma once

#include "GameComponent.h"
#include "AnimationData.h"


class Sprite : public GameComponent
{
public:
	Sprite(bool animated);
	~Sprite() = default;
	void tickComponent(GameStateData*  _GSD) override; // { return; }
	void renderComponent(RenderData*     _RD) override; // { return; }

	void setSpriteRECT(std::shared_ptr<RECT> rect) { sprite_src_rect = rect; }
	void setAnimationState(std::string  new_animation_state);

	void setSpriteAnimationFile(std::string  file_name);

private:
	void setAnimationFrame(RECT new_rect);
	bool is_animated = false;


	float					   total_time = 0.0f;
	std::shared_ptr<RECT>      sprite_src_rect;
	std::vector<AnimationData> anim_vector;
	int						   frame_index = 0;
	bool					   loop = true;
	AnimationData			   current_anim_state;  // the current anim state.
};