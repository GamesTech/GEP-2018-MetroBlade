#pragma once
#include "GameObject3D.h"
struct GameStateData;

class Camera :
	public GameObject3D
{
public:
	Camera(float _width, float _height, float _near, float _far);
	virtual ~Camera();

	void SetTarget(GameObject3D* _target) { m_targetObject = _target; }
	void SetTarget(Vector3 _target) { m_targetObject = NULL; m_targetPos = _target; }

	Matrix GetProj() { return m_proj; }
	Matrix GetView() { return m_view; }

	virtual void Tick(GameStateData* _GSD);
	virtual void Render(RenderData* _RD) {};

protected:
	GameObject3D* m_targetObject=NULL;
	Vector3 m_targetPos=Vector3::Zero;
	Matrix m_proj = Matrix::Identity;
	Matrix m_view = Matrix::Identity;
};

