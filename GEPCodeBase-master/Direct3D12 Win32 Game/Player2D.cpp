#include "pch.h"
#include "Player2D.h"
#include "GameStateData.h"
#include "Sprite.h"
Player2D::Player2D(RenderData* _RD, string _filename):Physics2D(_RD,_filename)
{
	src_rect.reset(new RECT);
	CentreOrigin();
	object_components.addComponent(new Sprite(true));
	sprite = object_components.getComponentByType<Sprite>();
	sprite->SetRECT(src_rect);
}


Player2D::~Player2D()
{
}

void Player2D::CheckInput()
{
	if (_GSD->m_keyboardState.Space)
	{
		action_state = JUMPING;
		phys_state = AIR;
	}
	//Push the guy around in the directions for the key presses
	if (_GSD->m_keyboardState.A)
	{
		AddForce(-m_drive * Vector2::UnitX);
		action_state = MOVING;
	}
	else if (_GSD->m_keyboardState.D)
	{
		AddForce(m_drive * Vector2::UnitX);
		action_state = MOVING;
	}
	else if (phys_state == GROUNDED && action_state != JUMPING)
	{
		//if no keys are pressed stop moving
		Vector2 zero_vel = Vector2(0, 0);
		SetVel(zero_vel);
	}
}
void Player2D::Tick(GameStateData* _GSD)
{

	switch (phys_state)
	{
	case GROUNDED:
		setGravity(0.0f);
		break;
	case AIR:
		break;
	}

	switch (action_state)
	{
	case IDLE:
		sprite->SetAnimation(IDLE_ANIM);
		break;
	case MOVING:
		if (phys_state == GROUNDED)
		{
			sprite->SetAnimation(MOVE_ANIM);
		}
		break;
	case JUMPING:
		
		sprite->SetAnimation(JUMP_ANIM);
		setGravity(1000.0f);
		AddForce(-jump_force * Vector2::UnitY);
		break;
	case ATTACKING:
		break;
	}
	
	//TEMP PLACE FOR INPUT WHILE INPUTMANAGER IS IN WORKS
		


	//change anim depending on gamestate - testing purposes
	if (GetVel() == Vector2(0,0) && phys_state == GROUNDED)
	{
		action_state = IDLE;
	}
	else if(GetVel() != Vector2(0, 0) && phys_state == GROUNDED)
	{
		action_state = MOVING;
	}

	//GRAVITY
	AddForce(gravity*Vector2::UnitY);

	//GEP:: Lets go up the inheritence and share our functionality

	Physics2D::Tick(_GSD);

	//Update sprite animation
	sprite->PlayAnimation(_GSD);

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
		phys_state = GROUNDED;
	}
	
}
