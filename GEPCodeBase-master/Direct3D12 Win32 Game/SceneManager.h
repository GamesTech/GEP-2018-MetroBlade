/** 
 *  @file    SceneManager.h
 *  @author  Nathan Butt (GitHub - n86-64)
 *  @date    13/02/2018  
 *  @version v1.0 
 *  
 *  @section System Module
 *           Core State Manager.
 *
 *  @brief Scene Manager system that handles the updating and rendering of levels.
 *
 *  @section Description
 *  
 *  Scene Manager is the component that is risponciable for the simulation and transition of scenes.
 *  Scene managers have a scene buffer which acts as a container for all active scenes. Upon recieving an update and render command the scene. Scenes can
 *	contain any combination of game objects. 
 */

#pragma once

#include <vector>

#include "Scene.h"
#include "GPUCommand.h"

namespace DX {
	class StepTimer;
}

struct GameStateData;

class GameObject3D;
class GameObject2D;
class Sound;

/**
*  Add Class Discription Here.
*/
class SceneManager 
{
public:
	SceneManager() = default;
	SceneManager(RenderData*  render_structure);

	void assignRenderData(RenderData* render_structure);

	void Init();
	void Update(GameStateData* game_state);
	void Render(ID3D12GraphicsCommandList* command_list);

	Scene*   getScene(); // Test routiene. 

	void loadScene(string scene_name);
	void loadScene(Scene* scene_name); // TODO - Move to a private variable.
	void clearScene();

	// Camera Viewports
	void setMainCamera(Camera* viewport_camera);

	// Game World Operations
	void instanciate2DObject(GameObject2D*  new_object);
	void instanciate3DObject(GameObject3D*  new_object);

private:
	void resetRenderState();

	std::unique_ptr<Scene>   current_scene;
	Camera*					 main_camera = nullptr;
	RenderData*				 render_data = nullptr;
};
