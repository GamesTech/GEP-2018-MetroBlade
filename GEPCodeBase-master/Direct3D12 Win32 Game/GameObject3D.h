#pragma once
#include "pch.h"

//Base 3D Game Object

using namespace DirectX;
using namespace DirectX::SimpleMath;
struct RenderData;
struct GameStateData;

//GEP:: Base 3D Game Object

//different Render types 
enum GO3D_Render_Type
{
	GO3D_RT_NONE = 0,
	GO3D_RT_PRIM = 1,
	GO3D_RT_GEOP = 2,
	GO3D_RT_SDK = 3,
	GO3D_RT_COUNT
};

class GameObject3D
{
public:
	GameObject3D();
	virtual ~GameObject3D();

	virtual void Tick(GameStateData* _GSD);
	virtual void Render(RenderData* _RD) = 0;

	void SetPos(Vector3 _pos) { m_pos = _pos; }
	void SetScale(float _scale) { m_scale = _scale * Vector3::One; }
	void SetScale( Vector3 _scale ){m_scale = _scale; }
	void SetOri(float _pitch, float _yaw, float _roll) { m_pitch = _pitch; m_yaw = _yaw, m_roll = _roll; }
	void SetOri(Vector3 _ori) { m_pitch = _ori.x; m_yaw = _ori.y; m_roll = _ori.z; }

	Vector3 GetPos() { return m_pos; }
	Vector3 GetScale() { return m_scale; }
	float GetPitch() { return m_pitch; }
	float GetYaw() { return m_yaw; }
	float GetRoll() { return m_roll; }
	Matrix GetOri() { return m_rot; }
	GO3D_Render_Type GetType() { return m_type; }

protected:
	Vector3 m_pos	= Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	float m_pitch	= 0.0f;
	float m_yaw		= 0.0f;
	float m_roll	= 0.0f;

	Matrix m_world = Matrix::Identity;
	Matrix m_rot = Matrix::Identity;

	GO3D_Render_Type m_type = GO3D_RT_NONE;
};

