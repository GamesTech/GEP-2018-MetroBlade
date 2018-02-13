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
 *  (Add a lengthy discription here of the source file.)
 */

#pragma once

#include <vector>

namespace DX {
	class StepTimer;
}

class GameStateData;

class GameObject3D;
class GameObject2D;
class Sound;

class RenderData;

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

	void loadScene(string scene_name);
	void clearScene();

	// Camera Viewports
	void setMainCamera(Camera* viewport_camera);

private:

	// Object Buffers
	std::vector<GameObject3D*> m_3DObjects; //
	std::vector<GameObject2D*> m_2DObjects;
	std::vector<Sound*> m_sounds;

	Camera*				main_camera = nullptr;
	
	// retrieved from gamestate.
	RenderData*			render_data = nullptr;
};
