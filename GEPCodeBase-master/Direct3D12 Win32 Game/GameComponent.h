#pragma once

struct GameStateData;
class  RenderData;

class GameComponent
{
public:
	GameComponent() = default;
	~GameComponent() = default;

	virtual void tickComponent(GameStateData*  _GSD);
	virtual void renderComponent(RenderData*     _RD);

};