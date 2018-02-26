#pragma once


class Scene;
class GameObject2D;

class WorldEvent 
{
public:
	WorldEvent() = default;
	WorldEvent(Scene* listening_scene);
	~WorldEvent() = default;

	void changeScene();
	void spawn2DObject(GameObject2D*  new_object);

private:
	Scene*		current_scene = nullptr;
};