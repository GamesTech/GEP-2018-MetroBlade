#pragma once
#include "Physics2D.h"
#include "Collider.h"

//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite

class Player2D :
	public Physics2D
{
public:
	//TODO: add a 3d player and modes to switch between different views and basic physics
	Player2D(RenderData* _RD, string _filename);
	virtual ~Player2D();

	virtual void Tick(GameStateData* _GSD);
	void collision();

	void SetDrive(float _drive) { m_drive = _drive; }
	float GetDrive() { return m_drive; }

	void SetLimit(Vector2 _lim) { m_limit = _lim; }
	Vector2 GetLimit() { return m_limit; }

protected:
	bool collided = false;
	float m_drive = 1.0f;
	float jump_force = 250000.0f;
	float gravity = 9.8f;
	float vertical_velocity;
	void setGravity(float gravity) { this->gravity = gravity; }
	enum GameStates { GROUNDED, JUMPING, FALLING };
	int game_states;
	float width = 20;
	float height = 20;

	Collider* col = new Collider(Vector2(m_pos), Vector2(0, 0), false);

	Vector2 m_limit = Vector2(800, 500);
};

