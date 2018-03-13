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

void Player2D::CheckInput(GameStateData* _GSD)
{
	//temp place for input
	if (_GSD->m_keyboardState.Space && phys_state == GROUNDED)
	{
		action_state = JUMPING;
		phys_state = AIR;
	}
	else if (_GSD->m_keyboardState.A)
	{
		m_effects = SpriteEffects_FlipHorizontally;
		SetVel(Vector2(-250, m_vel.y));
		action_state = MOVING;
	}
	else if (_GSD->m_keyboardState.D)
	{
		m_effects = SpriteEffects_None;
		SetVel(Vector2(250, m_vel.y));
		action_state = MOVING;
	}
	else if (phys_state == GROUNDED && action_state != JUMPING)
	{
		action_state = IDLE;
		SetVel(Vector2(0, 0));
	}
}
void Player2D::Tick(GameStateData* _GSD)
{
	
	CheckInput(_GSD);

	//physical state determines stuff like if they are colliding with ground, or walls or in the air
	switch (phys_state)
	{
	case GROUNDED:
		SetVel(Vector2(m_vel.x, 0));
		setGravity(0.0f);
		break;

	case AIR:

		break;
	}

	//action state determines the players action such as attacking, jumping, moving etc
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
		m_pos.y = 0.1f;
		
	}

	if (m_pos.x > m_limit.x)
	{
		m_pos.x = m_limit.x;
		
	}
	if (m_pos.y > m_limit.y)
	{
		m_pos.y = m_limit.y;
		phys_state = GROUNDED;
	}

	
	
}
