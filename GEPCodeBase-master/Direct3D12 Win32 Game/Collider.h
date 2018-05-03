#pragma once

#include <functional>

#include "GameObject2D.h"
#include "GameComponent.h"

#include "MetroBrawlCollisionData.h"

class Collider
	: public GameComponent
{
public:
	Collider() = default;
	Collider(Vector2  &origin, Vector2 dimensions, bool trigger = false);
	~Collider() = default;

	// Inherited via GameComponent
	virtual void tickComponent(GameStateData * _GSD) override;
	virtual void renderComponent(RenderData * _RD) override;

	int getTag();
	void setTag(int tag);

	float getMaxX();
	float getMaxY();
	bool getTrigger();

	Vector2 getBoxOrigin();
	void setBoxOrigin(Vector2 box_origin);
	Vector2 getMaxValues();

	void isColliderActive(bool is_active);
	bool isColliderActive() const;

	void isColliderImmediate(bool is_immediate);
	bool isColliderImmediate() const;

	void addParentObjectRefrence(GameObject2D* gameobject);

	void assignCollisionEvent(std::function<void(MetroBrawlCollisionData)>  func_delegate);
	void OnCollision(MetroBrawlCollisionData  col_data);

	GameObject2D*  getCollidersParent();

private:
	int m_tag;
	Vector2  box_dimensions;
	Vector2  box_origin;
	Vector2  max_values;
	bool is_trigger = false;

	bool is_collider_immediate = false;
	bool is_collider_active = true;

	GameObject2D*		parent_object = nullptr;

	std::function<void(MetroBrawlCollisionData)>	collision_event_deligate = nullptr;
};