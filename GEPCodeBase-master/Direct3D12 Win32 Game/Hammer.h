#pragma once
#include "Physics2D.h"
#include "Sprite.h"
class Hammer : public Physics2D
{
public:
	Hammer(RenderData* _RD, string _filename, Vector2 new_direction, Player2D* original);
	~Hammer();
	virtual void Tick(GameStateData* _GSD);
	virtual void Render(RenderData* _GSD);
	void attack(GameStateData* _GSD);
private:
	Sprite* sprite = nullptr;
	Collider* col = new Collider(Vector2(m_pos), Vector2(100, 130), false);
	Vector2 col_offset;
	Vector2 pos_offset;
	Player2D* player_original = nullptr;

	float damage_amount = 25.0f;

	const float max_time = 2.0f;
	float current_time = max_time;

	bool alive = true;



	void onCollision(MetroBrawlCollisionData  col_data);

};