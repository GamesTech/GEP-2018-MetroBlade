#pragma once

struct GameStateData;
class  RenderData;

class GameComponent
{
public:
	GameComponent() = default;
	virtual ~GameComponent() = default;

	virtual void tickComponent(GameStateData*  _GSD);
	virtual void renderComponent(RenderData*     _RD);

};

class TestComp : GameComponent 
{
public:
	TestComp() {};
	~TestComp() {};
	void tickComponent(GameStateData*  _GSD) override {};
	void renderComponent(RenderData*     _RD) override {};
};