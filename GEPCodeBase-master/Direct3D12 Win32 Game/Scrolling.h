#pragma once
#include "GameComponent.h"
#include "SceneManager.h"

class SceneManager;

class Scrolling : public GameComponent
{
public:
	Scrolling() = default;
	~Scrolling() = default;

	void loadImages();
	void renderImages(RenderData * _R);


private:
	std::unique_ptr<SceneManager> main_camera = nullptr;


	//Created vector of layers;
	//Each layer based upon distance from camera; 

};