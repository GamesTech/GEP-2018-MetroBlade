#include "pch.h"
#include "Physics2D.h"
#include "GameStateData.h"


Physics2D::Physics2D(RenderData* _RD, string _filename):ImageGO2D(_RD,_filename)
{
}


Physics2D::~Physics2D()
{
}

Vector2 Physics2D::GetInputVel() const
{
	return m_input_vel;
}

void Physics2D::SetInputVel(Vector2 _input_vel)
{
	m_input_vel = _input_vel;
}

Vector2 Physics2D::getDeltaPos() const
{
	return m_delta_pos;
}

//GEP:: Basic Euler Solver for point mass 
void Physics2D::Tick(GameStateData * _GSD)
{
	//VERY Basic idea of drag i.e. the faster I go the more I get pulled back
	m_delta_pos = m_pos;

	m_acc -= m_drag * m_vel;

	Vector2 newPos = m_pos + _GSD->m_dt * m_vel + (_GSD->m_dt * m_input_vel);
	Vector2 newVel = m_vel + _GSD->m_dt * m_acc;

	m_delta_pos = newPos - m_pos;
	m_pos = newPos;
	m_vel = newVel;
	m_acc = Vector2::Zero;
	m_input_vel = Vector2::Zero; // Reset movement input for next frame.
}



