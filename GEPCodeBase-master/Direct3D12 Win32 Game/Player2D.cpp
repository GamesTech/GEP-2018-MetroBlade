#include "pch.h"
#include "Player2D.h"
#include "GameStateData.h"
Player2D::Player2D(RenderData* _RD, string _filename):Physics2D(_RD,_filename)
{
	src_rect.reset(new RECT);
	src_rect->left = 0;
	src_rect->top = 0;
	src_rect->right = 128;
	src_rect->bottom = 128;
	CentreOrigin();
}


Player2D::~Player2D()
{
}
void Player2D::ChangeRectPos(int pos1, int pos2, int pos3, int pos4)
{
	src_rect->left = pos1;
	src_rect->top = pos2;
	src_rect->right = pos3;
	src_rect->bottom = pos4;
}

void Player2D::PlayAnimation(GameStateData* _GSD)
{
	anim_time += _GSD->m_dt;
	switch (current_anim)
	{
		case IDLE_ANIM:
			
			if (anim_time < 0.5f)
			{
				ChangeRectPos(0, 0, 100, 126);
			}
			else if (anim_time > 0.5f && anim_time < 1.0f)
			{
				ChangeRectPos(100, 0, 199, 126);
			}
			else if(anim_time > 1.0f)
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

void Player2D::Tick(GameStateData* _GSD)
{
	PlayAnimation(_GSD);
	if (game_states == GROUNDED)
	{
		current_anim = MOVE_ANIM;
		setGravity(0.0f);
		if (_GSD->m_keyboardState.Space)
		{
			setGravity(1000.0f);
			game_states = JUMPING;
			AddForce(-jump_force * Vector2::UnitY);
		}
	}

	if (_GSD->m_keyboardState.J)
	{
		Vector2 test_vel = Vector2(0, 0);
		SetVel(test_vel);
	}

	//change anim depending on gamestate - testing purposes
	if (GetVel() == Vector2(0,0) && game_states == GROUNDED)
	{
		current_anim = IDLE_ANIM;
	}
	else if(GetVel() != Vector2(0, 0) && game_states == GROUNDED)
	{
		current_anim = MOVE_ANIM;
	}
	else if (game_states == JUMPING)
	{
		current_anim = JUMP_ANIM;
	}
	AddForce(gravity*Vector2::UnitY);
//Push the guy around in the directions for the key presses

	if (_GSD->m_keyboardState.A)
	{
		AddForce(-m_drive * Vector2::UnitX);
		if (game_states == GROUNDED)
		{
			
		}
	}
	if (_GSD->m_keyboardState.D)
	{
		AddForce(m_drive * Vector2::UnitX);
		if (game_states == GROUNDED)
		{
			
		}
	}
	

	
//GEP:: Lets go up the inheritence and share our functionality

	Physics2D::Tick(_GSD);

//after that as updated my position let's lock it inside my limits
	if (m_pos.x < 50.0f)
	{
		m_pos.x = 1.0f;
		
	}
	if (m_pos.y <= 0.0f)
	{
		m_pos.y = 0.0f;
		
	}

	if (m_pos.x > m_limit.x)
	{
		m_pos.x = m_limit.x;
		
	}
	if (m_pos.y >= m_limit.y)
	{
		m_pos.y = m_limit.y;
		game_states = GROUNDED;
	}
	
}
