#pragma once

#include "Physics2D.h"
#include "Sprite.h"
#include "InputManager.h"
//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite

class Player2D :
	public Physics2D
{
public:

	//TODO: add a 3d player and modes to switch between different views and basic physics
	Player2D(RenderData* _RD, string _filename, int gamepadID);
	virtual ~Player2D();

	virtual void Tick(GameStateData* _GSD);
	void CheckInput(GameStateData* _GSD);
	void SetDrive(float _drive) { m_drive = _drive; }
	float GetDrive() { return m_drive; }
	void SetLimit(Vector2 _lim) { m_limit = _lim; }
	bool IsAttacking() { return attacking; }
	Vector2 GetLimit() { return m_limit; }
	
	void setStateGrounded();
	void setStateFalling();
	void punched(GameStateData* _GFD, Vector2 direction);


	// Game Manager interface
	bool			isDead() const;
	void			isDead(bool is_dead);
	Player2D*		getKiller() const;
	float			getRespawnTime() const;
	void			setRespawnTime(float respawn_timer);

	Vector2 getDirection() { return direction; }

protected:

	enum PhysicalStates {
		GROUNDED,
		AIR,
		COLLISION
	};

	enum PlayerActions {
		IDLE,
		MOVING,
		ATTACKING,
		JUMPING
	};

	Sprite*				sprite;
	bool flipped = false;

	Collider* col = new Collider(Vector2(m_pos), Vector2(100, 130), false);
	Collider* punch_collider = new Collider(Vector2(m_pos), Vector2(0, 0), true);

	Vector2 offset;
	float m_drive = 1.0f;
	float x_speed = 100.0f;
	int controller_id = 0;
	Vector2 m_limit = Vector2(800, 500);
	InputManager* m_input;
	float jump_force = 1000000.0f;
	float gravity = 981.0f;
	float vertical_velocity;
	Vector2 direction = Vector2(0, 0);
	bool attacking = false;
	void setGravity(float gravity) { this->gravity = gravity; }
	PhysicalStates phys_state = GROUNDED;
	PlayerActions action_state = IDLE;
	bool				dead = false;
	Player2D*			killer = nullptr;
	float				respawn_time = 0.0f;

private:
	// Event Handlers for collision.
	void onCollision(MetroBrawlCollisionData  col_data);
	void onPunchCollision(MetroBrawlCollisionData  col_data);
};