/**
*  @file    Item.h
*  @author  Elliot Martin (GitHub - Elliotmartin97)
*  @date    14/05/2018
*  @version v1.0
*
*  @section GameObject Item
*           
*
*  @brief Base Item for pickup by players
*
*  @section Description
*
*  Holds a pickup item and passes that to the player which picks it up
*  changing the use function depending on item type
*/
#pragma once
#include "Physics2D.h"
#include "Sprite.h"

class Bomb;
class Hammer;
class Projectile;
class Player2D;
enum ItemType {
	HEALTH,
	PROJECTILE,
	HAMMER,
	BOMB
};
enum ItemState {
	NONE,
	PICKUP,
	USEABLE
};
class Item : public Physics2D
{
public:
	Item(RenderData* _RD, string _filename, Vector2 position, int item_num);
	virtual ~Item();

	Vector2 GetPostion() { return pos; }
	void SetPosition(Vector2 new_pos);

	ItemType GetType() { return item_type; }

	virtual void Tick(GameStateData* _GSD);
	virtual void Render(RenderData* _GSD);
	void UseItem(RenderData* _RD, Player2D* player, ItemType type);
private:
	bool respawning = false;
	float max_time = 1.0f;
	float respawn_time = max_time;
	Vector2 item_pos = Vector2::Zero;
	Sprite* sprite;
	Collider* col = new Collider(Vector2(m_pos), Vector2(100, 130), true);
	Vector2 pos = Vector2::Zero;
	ItemType item_type = ItemType::HEALTH;
	ItemState item_state = ItemState::PICKUP;
	const int health_amount = 25;
	float gravity = 150.0f;
	Projectile* proj = nullptr;
	Hammer* ham = nullptr;
	Bomb* bomb = nullptr;
	void onCollision(MetroBrawlCollisionData  col_data);
};