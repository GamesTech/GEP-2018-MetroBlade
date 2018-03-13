#pragma once

class GameStateData;
struct RenderData;

class GameObject 
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Tick(GameStateData* _GSD) = 0;
	virtual void Render(RenderData* _RD) = 0;
};