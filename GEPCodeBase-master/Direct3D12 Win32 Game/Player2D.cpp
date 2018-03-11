#include "pch.h"
#include "Player2D.h"
#include "GameStateData.h"

Player2D::Player2D(RenderData* _RD, string _filename):Physics2D(_RD,_filename)
{
	CentreOrigin();
}


Player2D::~Player2D()
{
}

void Player2D::Tick(GameStateData * _GSD)
{
	if (game_states == GROUNDED)
	{
		setGravity(0.0f);
		if (_GSD->m_keyboardState.Space)
		{
			setGravity(1000.0f);
			game_states = JUMPING;
			AddForce(-jump_force * Vector2::UnitY);
		}
	}
	AddForce(gravity*Vector2::UnitY);
//Push the guy around in the directions for the key presses

	if (_GSD->m_keyboardState.A)
	{
		AddForce(-m_drive * Vector2::UnitX);
	}
	if (_GSD->m_keyboardState.D)
	{
		AddForce(m_drive * Vector2::UnitX);
	}
	
	if (_GSD->m_keyboardState.Escape) 
	{
		// Testing for error components. 
		world.exitGame();
	}

//GEP:: Lets go up the inheritence and share our functionality

	Physics2D::Tick(_GSD);

//after that as updated my position let's lock it inside my limits
	if (m_pos.x < 0.0f)
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
