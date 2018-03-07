/**
*  @file    GameComponent.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    07/03/2018
*  @version v1.0
*
*  @section System Module
*           Component System Module.
*
*  @brief A Component is a basic primative that forms part of a game object. 
*
*  @section Description
*
*  Game Components are the base object that perform some type of core operation. 
*  For example a sound component which will allow a game object to play sound
*  in the world. 
*/

#pragma once

struct GameStateData;
struct RenderData;

class GameComponent
{
public:
	GameComponent() = default;
	virtual ~GameComponent() = default;

	virtual void tickComponent(GameStateData*  _GSD) = 0;
	virtual void renderComponent(RenderData*     _RD) = 0;

	std::string getTag() const;
	void		setTag(std::string new_tag);

protected:
	std::string				tag;
};