#include "pch.h"
#include "Player2D.h"
#include "GameStateData.h"
#include "PlayerStatus.h"

#include "Sprite.h"
#include "SpriteAnimFileReader.h"


Player2D::Player2D(RenderData* _RD, string _filename):Physics2D(_RD,_filename)
{
	src_rect.reset(new RECT);
	CentreOrigin();
	object_components.addComponent(new PlayerStatus);
	object_components.addComponent(new Sprite(true));
	sprite = object_components.getComponentByType<Sprite>();
	sprite->setSpriteRECT(src_rect);
	sprite->setSpriteAnimationFile("Fighter_1_animations");
	sprite->setAnimationState("idle");
}


Player2D::~Player2D()
{
}

void Player2D::Tick(GameStateData* _GSD)
{

	if (game_states == GROUNDED)
	{
		
		setGravity(0.0f);
		if (_GSD->m_keyboardState.Space)
		{
			setGravity(100.0f);
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
		sprite->setAnimationState("idle");
		//sprite->SetAnimation(IDLE_ANIM);
	}
	else if(GetVel() != Vector2(0, 0) && game_states == GROUNDED)
	{
		sprite->setAnimationState("move");
		//sprite->SetAnimation(MOVE_ANIM);
	}
	else if (game_states == JUMPING)
	{
		sprite->setAnimationState("jump");
		//sprite->SetAnimation(JUMP_ANIM);
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
	else if (_GSD->m_keyboardState.D)
	{
		AddForce(m_drive * Vector2::UnitX);
		if (game_states == GROUNDED)
		{
			
		}
	}
	else if(game_states == GROUNDED)
	{
		Vector2 test_vel = Vector2(0, 0);
		SetVel(test_vel);
	}
	
	if (_GSD->m_keyboardState.Escape) 
	{
		// Testing for error components. 
		world.exitGame();
	}

	
//GEP:: Lets go up the inheritence and share our functionality

	Physics2D::Tick(_GSD);

	//Update sprite animation
	sprite->tickComponent(_GSD);

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

bool Player2D::isDead() const
{
	return dead;
}

Player2D* Player2D::getKiller() const
{
	return killer;
}

Collider Player2D::getCollider()
{
	return *col;
}

