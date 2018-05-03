#pragma once
#include "ImageGO2D.h"

class Player2D;
enum ItemType {
	SPEED,
	HEALTH,
	PROJECTILE
};
enum ItemState {
	NONE,
	PICKUP,
	USEABLE
};
class Item : public ImageGO2D
{
public:
	Item(RenderData* _RD, string _filename, ItemType type);
	virtual ~Item();

	Vector2 GetPostion() { return pos; }
	void SetPosition(Vector2 new_pos);

	ItemType GetType() { return item_type; }

	virtual void Tick(GameStateData* _GSD);
	virtual void Render(RenderData* _GSD);

	void UseItem(Player2D* player, ItemType type);

private:
	Collider* col = new Collider(Vector2(m_pos), Vector2(100, 130), false);
	Vector2 pos = Vector2::Zero;
	ItemType item_type = ItemType::HEALTH;
	ItemState item_state = ItemState::PICKUP;
	const int health_amount = 25;
	void onCollision(MetroBrawlCollisionData  col_data);
};