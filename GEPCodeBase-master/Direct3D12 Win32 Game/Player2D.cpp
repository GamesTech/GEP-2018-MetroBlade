#include "pch.h"

#include "Player2D.h"
#include "GamePad.h"
#include "GameStateData.h"
#include "PlayerStatus.h"

#include "Sprite.h"
#include "SpriteAnimFileReader.h"


Player2D::Player2D(RenderData* _RD, string _filename, int gamepadID):Physics2D(_RD,_filename)
{
	using namespace std::placeholders;

	src_rect.reset(new RECT);
	CentreOrigin();
	object_components.addComponent(new PlayerStatus);
	object_components.addComponent(new Sprite(true));

	// Add Colliders to the players.
	col->isColliderImmediate(true);
	col->addParentObjectRefrence(this);
	punch_collider->addParentObjectRefrence(this);

	col->assignCollisionEvent(std::bind(&Player2D::onCollision, this, _1));
	punch_collider->assignCollisionEvent(std::bind(&Player2D::onPunchCollision, this, _1));

	object_components.addComponent(col);
	object_components.addComponent(punch_collider);

	sprite = object_components.getComponentByType<Sprite>();
	sprite->setSpriteRECT(src_rect);
	sprite->setSpriteAnimationFile(_filename + "_animations");
	sprite->setAnimationState("idle");

	SoundComponent*	  test_sound = new SoundComponent("Explo1");
	object_components.addComponent(test_sound);

	controller_id = gamepadID;
	_playerRD = _RD;
}


Player2D::~Player2D()
{

}

void Player2D::CheckInput(GameStateData* _GSD)
{
	// Consider moving these into seperate functions.
	if (_GSD->input->getBindDown("Jump",controller_id))
	{
		if (phys_state == GROUNDED)
		{
			action_state = JUMPING;
			sprite->setAnimationState("jump");
			AddForce(-jump_force * Vector2::UnitY);
			phys_state = AIR;
			object_components.getComponentByType<SoundComponent>()->Play();
		}
	}

	if (_GSD->input->getBindDown("Attack", controller_id))
	{
		if (phys_state == GROUNDED)
		{
			action_state = ATTACKING;
		}
	}
	else 
	{
		action_state = IDLE;
	}

	// TODO - Change this to multiply the 
	if (_GSD->input->getBindRawValue("Move", controller_id) < 0)
	{
		offset = Vector2(-20, 0);
		m_effects = SpriteEffects_FlipHorizontally;
	}
	else if (_GSD->input->getBindRawValue("Move", controller_id) > 0)
	{
		offset = Vector2(120, 0);
		m_effects = SpriteEffects_None;
	}

	direction = Vector2(_GSD->input->getBindRawValue("Move", controller_id) * 1, 0);
	SetInputVel(Vector2(_GSD->input->getBindRawValue("Move", controller_id) * x_speed, 0));

	if (GetInputVel() != Vector2::Zero) 
	{
		action_state = MOVING;
	}

	if (_GSD->input->getBindDown("Use", controller_id))
	{
		action_state = USE;
	}
	
}

void Player2D::Tick(GameStateData* _GSD)
{
	punch_collider->setBoxOrigin(m_pos + offset);
	col->setBoxOrigin(m_pos);
	CheckInput(_GSD);

	//physical state determines stuff like if they are colliding with ground, or walls or in the air

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
			break;

		case ATTACKING:
			attacking = true;
			sprite->setAnimationState("attack");
			break;
	
		case USE:
			if (player_item)
			{
				player_item->UseItem(_playerRD, this, player_item->GetType());
				player_item = nullptr;
			}
			break;
	}

	if (phys_state == AIR) 
	{
		sprite->setAnimationState("jump");
	}

	//if (_GSD->m_keyboardState.Escape)
	//{
	//	// Testing for error components.

	//	// Clear the scene for now. Later on we should open a pause menu to have the option to exit the game. 
	//	world.changeScene("clear"); 
	//}

	//GRAVITY
	m_acc += (gravity * Vector2::UnitY);

	//GEP:: Lets go up the inheritence and share our functionality
	Physics2D::Tick(_GSD);

	//Update sprite animation
	sprite->tickComponent(_GSD);

	if (m_pos.y > 1500) // TODO - Change this to be collision based.
	{
		dead = true;
	}
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

void Player2D::onCollision(MetroBrawlCollisionData col_data)
{
	// Calculate there normals and apply a force to them.
	// Currently in 'test' state. Will be changed to the above algorithm later.

	// printf("LOL"); 
}

void Player2D::onPunchCollision(MetroBrawlCollisionData col_data)
{
	printf("We can now detect punches.");
}

void Player2D::punched(GameStateData * _GSD, Vector2 direction)
{
	AddForce(10000 * direction * Vector2::UnitX);
}

void Player2D::setStateGrounded()
{
	phys_state = GROUNDED;
}

void Player2D::setStateFalling()
{
}

void Player2D::AddItem(Item* obj, int uses)
{
	player_item = obj;
}

