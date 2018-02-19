/**
*  @file    Scene.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    14/02/2018
*  @version v1.0
*
*  @section System Module
*           Core State Manager.
*
*  @brief Scenes are game worlds which is where the simulation takes place.
*
*  @section Description
*
*  
*/

#pragma once

#include <string>

#include "GameStateData.h"

struct RenderData;

class Scene 
{
public:
	Scene() = default;
	~Scene();

	void Update(GameStateData* game_state);
	void Render(RenderData* render_data, ID3D12GraphicsCommandList* command_list);

	// Temporary functions to add objects to the scene.
	void add2DGameObjectToScene(GameObject2D* new_object);
	void add3DGameObjectToScene(GameObject3D* new_object);

private:
	/* Metadata */
	std::string scene_name = "NULL";

	/* Object Buffers */
	std::vector<GameObject3D*> m_3DObjects; 
	std::vector<GameObject2D*> m_2DObjects;

};