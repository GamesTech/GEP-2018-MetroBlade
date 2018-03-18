#pragma once
#include "Physics2D.h"
#include "Collider.h"
#include "Sprite.h"
//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite

class Player2D :
	public Physics2D
	
{
public:
	//TODO: add a 3d player and modes to switch between different views and basic physics
	Player2D(RenderData* _RD, string _filename);
	virtual ~Player2D();


	virtual void Tick(GameStateData* _GSD);

	void SetDrive(float _drive) { m_drive = _drive; }
	float GetDrive() { return m_drive; }
	void SetLimit(Vector2 _lim) { m_limit = _lim; }
	Vector2 GetLimit() { return m_limit; }
	Collider getCollider();


	// Game Manager interface
	bool			isDead() const;
	void			isDead(bool is_dead);
	Player2D*		getKiller() const;
	float			getRespawnTime() const;
	void			setRespawnTime(float respawn_timer);


protected:
	Sprite*				sprite;
//	std::unique_ptr<Sprite> sprite;
	Collider * col = new Collider(Vector2(m_pos), Vector2(100, 130), false);
	float m_drive = 1.0f;
	float jump_force = 25000.0f;
	float gravity = 9.8f;
	float vertical_velocity;

	void setGravity(float gravity) { this->gravity = gravity; }

	enum GameStates { GROUNDED,JUMPING,	FALLING };

	int game_states;

	bool				dead = false;
	Player2D*			killer = nullptr;
	float				respawn_time = 0.0f;


	Vector2 m_limit = Vector2(800, 500);
};