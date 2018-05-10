#pragma once
#include "Physics2D.h"

class Bomb : public Physics2D
{
public:
	Bomb(RenderData* _RD, string _filename, Vector2 new_direction, Player2D* original);
	~Bomb();
	virtual void Tick(GameStateData* _GSD);
	virtual void Render(RenderData* _GSD);
	void explode(GameStateData* _GSD);
private:
	Sprite* sprite = nullptr;
	Collider* col = new Collider(Vector2(m_pos), Vector2(100, 130), false);
	Collider* hit_col = new Collider(Vector2(m_pos), Vector2(200, 200), false);
	const float max_time = 3.0f;
	float current_time = max_time;
	float explosion_time = 1.0f;
	void onCollision(MetroBrawlCollisionData  col_data);
	void hitOnCollision(MetroBrawlCollisionData  col_data);
};