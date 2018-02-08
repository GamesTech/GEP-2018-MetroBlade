#pragma once
#include "pch.h"

//GEP:: Base class for all 2-D objects

using namespace DirectX;
using namespace DirectX::SimpleMath;
struct RenderData;
struct GameStateData;

class GameObject2D
{
public:
	GameObject2D();
	virtual ~GameObject2D();

	Vector2 GetPos() { return m_pos; }
	Vector2 GetOrigin() { return m_origin; }
	float GetOri() { return m_orientation; }
	Color GetColour() { return m_colour; }
	Vector2 GetScale() { return m_scale; }

	void SetPos(Vector2 _pos) { m_pos = _pos; }
	void SetOrigin(Vector2 _origin) { m_origin = _origin; }
	void SetOri(float _ori) { m_orientation = _ori; }
	void SetColour(Color _col) { m_colour = _col; }
	void SetScale(Vector2 _scale) { m_scale = _scale; }


	virtual void CentreOrigin() = 0;

	virtual void Tick(GameStateData* _GSD) {};
	virtual void Render(RenderData* _RD) = 0;

protected:
	Vector2 m_pos = Vector2::Zero;
	Vector2 m_origin = Vector2::Zero;
	float m_orientation = 0.0f;
	Color m_colour = Colors::White;
	Vector2 m_scale = Vector2::One;

};

