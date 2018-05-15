#include "pch.h"

#include "Player2D.h"
#include "GamePad.h"
#include "GameStateData.h"
#include "PlayerStatus.h"

#include "Sprite.h"
#include "SpriteAnimFileReader.h"

#include "LobbySystem.h"


Player2D::Player2D(RenderData* _RD, string _filename, int gamepadID, Vector2(dimensions)) :Physics2D(_RD, _filename)
{
	using namespace std::placeholders;

	col = new Collider(Vector2(m_pos), Vector2(dimensions), false);
	punch_collider = new Collider(Vector2(col->getBoxMidpoint().x, m_pos.y), Vector2(col->getBoxDimenstions().x / 2, col->getBoxDimenstions().y), true);

	src_rect.reset(new RECT);
	CentreOrigin();
	object_components.addComponent(new PlayerStatus);
	object_components.addComponent(new LobbySystemComponent);
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
	if (_GSD->input->getBindDown("Jump", controller_id))
	{
		if (phys_state == GROUNDED)
		{
			action_state = JUMPING;
			sprite->setAnimationState("jump");
			SetVel(Vector2(GetVel().x, GetVel().y - jump_force));
			// AddForce(-jump_force * Vector2::UnitY);
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
	if (_GSD->input->getBindRawValue("Move", controller_id) < 0 || _GSD->input->getBindDown("MoveLeft", controller_id))
	{
		offset = Vector2(-20, 0);
		m_effects = SpriteEffects_FlipHorizontally;
		direction.x = -1;
	}
	else if (_GSD->input->getBindRawValue("Move", controller_id) > 0 || _GSD->input->getBindDown("MoveRight", controller_id))
	{
		offset = Vector2(0, 0);
		m_effects = SpriteEffects_None;
		direction.x = 1;
	}


	//direction = Vector2(_GSD->input->getBindRawValue("Move", controller_id) * 1, controller_id);
	SetInputVel
	(
		Vector2
		(
			getInputDirection(_GSD->input->getBindRawValue("Move", controller_id),
				_GSD->input->getBindDown("MoveLeft", controller_id),
				_GSD->input->getBindDown("MoveRight", controller_id))
			* x_speed
			, 0
		)
	);

	if (GetInputVel() != Vector2::Zero)
	{
		action_state = MOVING;
	}

	if (_GSD->input->getBindDown("Use", controller_id))
	{
		action_state = USE;
	}

	// Test Code
	//if (_GSD->input->getBindDown("Action", controller_id)) 
	//{
	//	object_components.getComponentByType<LobbySystemComponent>()->addPlayer(PlayerData());
	//}

}

void Player2D::Tick(GameStateData* _GSD)
{
	punch_collider->setBoxOrigin(Vector2(col->getBoxMidpoint().x, m_pos.y) + offset);
	col->setBoxOrigin(m_pos);
	CheckInput(_GSD);


	attacking = false;

	if (!canAttack)
	{
		current_time -= _GSD->m_dt;
		if (current_time <= 0)
		{
			canAttack = true;
		}
	}


	
	//physical state determines stuff like if they are colliding with ground, or walls or in the air

	//action state determines the players action such as attacking, jumping, moving etc

	switch (action_state)
	{
	case ATTACKING:
		if (canAttack)
		{
			attacking = true;
			canAttack = false;
			sprite->setAnimationState("attack");
			current_time = max_time;
		}
		break;
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

int Player2D::getInputDirection(int analog_value, int left_dpad_value, int right_dpad_value)
{
	if (analog_value != 0)
	{
		return analog_value;
	}
	else
	{
		return returnDPadDirectionValue(left_dpad_value, right_dpad_value);
	}
}

int Player2D::returnDPadDirectionValue(bool left_bind, bool right_bind)
{
	return (int)right_bind - (int)left_bind;
}

void Player2D::onCollision(MetroBrawlCollisionData col_data)
{
	// Calculate there normals and apply a force to them.
	// Currently in 'test' state. Will be changed to the above algorithm later.

	// printf("LOL"); 
}

void Player2D::onPunchCollision(MetroBrawlCollisionData col_data)
{
	Player2D* player = dynamic_cast<Player2D*>(col_data.collider_object->getCollidersParent());
	if (player)
	{
		if (player != this)
		{
			double target_damage_percentage = player->getComponentManager()->getComponentByType<PlayerStatus>()->getDamagePercentage();
			if (attacking)
			{
				static_cast<Physics2D*>(col_data.collider_object->getCollidersParent())->AddForce((punch_force + (punch_force*target_damage_percentage)) * Vector2::UnitX * direction);

				player->getComponentManager()->getComponentByType<PlayerStatus>()->setDamagePercentage(target_damage_percentage + 20);
			}
		}
	}
	/*int target_damage_percentage = col_data.collider_object->*/

	printf("We can now detect punches.");

}

bool Player2D::hasItem()
{
	if (player_item)
	{
		return true;
	}
	else
	{
		return false;
	}
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

