#include "pch.h"
#include "Player2D.h"
#include "GamePad.h"
#include "GameStateData.h"
#include "PlayerStatus.h"

#include "Sprite.h"
#include "SpriteAnimFileReader.h"


Player2D::Player2D(RenderData* _RD, string _filename, int gamepadID):Physics2D(_RD,_filename)

{
	src_rect.reset(new RECT);
	CentreOrigin();
	object_components.addComponent(new PlayerStatus);
	object_components.addComponent(new Sprite(true));
	sprite = object_components.getComponentByType<Sprite>();
	sprite->setSpriteRECT(src_rect);
	sprite->setSpriteAnimationFile("Fighter_1_animations");
	sprite->setAnimationState("idle");
	controller_id = gamepadID;
}


Player2D::~Player2D()
{
}

void Player2D::CheckInput(GameStateData* _GSD)
{
	DirectX::GamePad::State controller_state = _GSD->m_gamePad->GetState(controller_id);
	float stick_x = controller_state.thumbSticks.leftX;
	//temp place for input
	if (_GSD->m_keyboardState.Space || controller_state.IsAPressed())
	{
		if (phys_state == GROUNDED)
		{
			action_state = JUMPING;
			phys_state = AIR;
		}
	}
	else if (_GSD->m_keyboardState.F || controller_state.IsXPressed())
	{
		if (phys_state == GROUNDED)
		{
			action_state = ATTACKING;
			//SetVel(Vector2(0, 0));
		}

	}
	else if (_GSD->m_keyboardState.A || stick_x < 0)
	{
		offset = Vector2(-20, 0);
		direction = Vector2(-1, 0);
		m_effects = SpriteEffects_FlipHorizontally;
		//SetVel(Vector2(-x_speed, m_vel.y));
		action_state = MOVING;
		AddForce(-m_drive * Vector2::UnitX);
	}
	else if (_GSD->m_keyboardState.D || stick_x > 0)
	{
		offset = Vector2(120, 0);
		direction = Vector2(1, 0);
		m_effects = SpriteEffects_None;
		//SetVel(Vector2(x_speed, m_vel.y));
		action_state = MOVING;
		AddForce(m_drive * Vector2::UnitX);
	}
	else if (phys_state == GROUNDED && action_state != JUMPING)
	{
		action_state = IDLE;
		//SetVel(Vector2(0, 0));
	}
	
	if (_GSD->m_keyboardState.J)
	{
		dead = true;
	}

}
void Player2D::Tick(GameStateData* _GSD)
{
	punch_collider->setBoxOrigin(m_pos + offset);
	col->setBoxOrigin(m_pos);
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
	attacking = false;
	switch (action_state)
	{

	case IDLE:

		sprite->setAnimationState("idle");
		break;

	case MOVING:

		if (phys_state == GROUNDED)
		{
			sprite->setAnimationState("move");
		}
		break;

	case JUMPING:

		sprite->setAnimationState("jump");
		setGravity(1000.0f);
		AddForce(-jump_force * Vector2::UnitY);
		break;

	case ATTACKING:
		attacking = true;
		sprite->setAnimationState("attack");
		break;
	
		

	}
	if (_GSD->m_keyboardState.Escape)
	{
		// Testing for error components. 
		world.exitGame();
	}

	//GRAVITY
	AddForce(gravity*Vector2::UnitY);

	//GEP:: Lets go up the inheritence and share our functionality

	Physics2D::Tick(_GSD);

	//Update sprite animation
	sprite->tickComponent(_GSD);

//after that as updated my position let's lock it inside my limits
	/*if (m_pos.x < 50.0f)
	{
		m_pos.x = 1.0f;
		m_vel.x = 0.0f;

	}*/
	if (m_pos.y <= 0.0f)
	{
		m_pos.y = 0.1f;
		
	}

	/*if (m_pos.x > m_limit.x)
	{
		m_pos.x = m_limit.x;
		m_vel.x = 0.0f;

	}*/
	if (m_pos.y > m_limit.y)
	{
		m_pos.y = m_limit.y;
		phys_state = GROUNDED;
	}

	Physics2D::Tick(_GSD);

}

bool Player2D::isDead() const
{
	return dead;
}

void Player2D::isDead(bool is_dead)
{
	dead = is_dead;
}

Player2D* Player2D::getKiller() const
{
	return killer;
}

float Player2D::getRespawnTime() const
{
	return respawn_time;
}

void Player2D::setRespawnTime(float respawn_timer)
{
	respawn_time = respawn_timer;
}

Collider* Player2D::getCollider(int id)
{

	switch (id)
	{
	case 0:
		return col;
		break;
	case 1:
		return punch_collider;
		break;
	}
}

void Player2D::punched(GameStateData * _GSD, Vector2 direction)
{
	
	AddForce(10000 * direction * Vector2::UnitX);
}

