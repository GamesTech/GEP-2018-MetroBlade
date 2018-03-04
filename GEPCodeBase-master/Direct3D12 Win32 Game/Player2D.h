#pragma once
#include "Physics2D.h"

//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite
enum animation
{
	IDLE_ANIM,
	MOVE_ANIM,
	JUMP_ANIM,
	ATTACK_ANIM
};
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
	void ChangeRectPos(int pos1, int pos2, int pos3, int pos4) override;
	void PlayAnimation(GameStateData* _GSD);
	void SetLimit(Vector2 _lim) { m_limit = _lim; }
	Vector2 GetLimit() { return m_limit; }

protected:
	animation current_anim = IDLE_ANIM;
	float anim_time = 0.0f;
	float m_drive = 1.0f;
	float jump_force = 25000.0f;
	float gravity = 9.8f;
	float vertical_velocity;
	void setGravity(float gravity) { this->gravity = gravity; }
	enum GameStates { 
		GROUNDED,
		JUMPING,
		FALLING
	};
	int game_states;

	Vector2 m_limit = Vector2(800, 500);
};

