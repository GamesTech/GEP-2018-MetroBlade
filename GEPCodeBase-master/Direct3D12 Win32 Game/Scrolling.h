#pragma once
#include "GameComponent.h"
#include "SceneManager.h"
#include "Layers.h"

class SceneManager;

class Scrolling : public GameComponent
{
public:
	Scrolling() = default;
	~Scrolling() = default;

	void setLayerSpeed();

private:
	std::unique_ptr<SceneManager> main_camera = nullptr;
	std::unique_ptr<Layers> layers[5];

	//Created vector of layers; class file?
	//Each layer based upon distance from camera; 

};