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

	setGravity(1000.0f);
	AddForce(gravity*Vector2::UnitY);
	int game_state = GROUNDED;
	switch (game_state)
	{
	case GROUNDED:
	{
		setGravity(0.0f);
		break;
	}
	case JUMPING:
	{
		setGravity(0.0f);
		break;
	}

	case FALLING:
	{
		setGravity(1000.0f);
		break;
	}
	}

//Push the guy around in the directions for the key presses
	if (_GSD->m_keyboardState.Space)
	{
		game_state = JUMPING;
		AddForce(-jump_force * Vector2::UnitY);	
	}
	if (_GSD->m_keyboardState.A)
	{
		AddForce(-m_drive * Vector2::UnitX);
	}
	if (_GSD->m_keyboardState.D)
	{
		AddForce(m_drive * Vector2::UnitX);
	}

	Vector2 mousePush = Vector2(_GSD->m_mouseState.x, _GSD->m_mouseState.y);
	
	AddForce(m_drive*mousePush);
	
//GEP:: Lets go up the inheritence and share our functionality

	Physics2D::Tick(_GSD);

//after that as updated my position let's lock it inside my limits
	if (m_pos.x < 0.0f)
	{
		m_pos.x = 1.0f;
		
	}
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 1.0f;
		game_state = GROUNDED;
	}

	if (m_pos.x > m_limit.x)
	{
		m_pos.x =  m_limit.x - 2.0f;
		
	}
	if (m_pos.y > m_limit.y)
	{
		m_pos.y = m_limit.y - 1.0f;	
	}
	
}
