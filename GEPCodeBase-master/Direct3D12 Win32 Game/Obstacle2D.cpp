#include "pch.h"
#include "Obstacle2D.h"
#include "GameStateData.h"
#include "PlayerStatus.h"

#include "Sound.h"

#include "Sprite.h"
#include "SpriteAnimFileReader.h"


Obstacle2D::Obstacle2D(RenderData* _RD, string _filename, Vector2 dimensions): ImageGO2D(_RD, _filename)
{
	col = new Collider(Vector2(m_pos), Vector2(dimensions), true);
	col->isColliderActive(true);
	col->addParentObjectRefrence(this);
	object_components.addComponent(col);

	// Testing the sound system.
	SoundComponent*	  test_sound = new SoundComponent("across-the-border");
	test_sound->isLooped(true);
	object_components.addComponent(test_sound);
}

Obstacle2D::~Obstacle2D()
{
}

void Obstacle2D::Tick(GameStateData* _GSD)
{
	col->setBoxOrigin(Vector2(m_pos));
	m_origin = Vector2(100,100);
	
	//change anim depending

	//GEP:: Lets go up the inheritance and share our functionality

	if (_GSD->m_keyboardState.IsKeyDown(Keyboard::Tab)) 
	{
		object_components.getComponentByType<SoundComponent>()->Play();
	}
}

void Obstacle2D::onObjectCollision(MetroBrawlCollisionData col_data)
{
	// This works but doing collisions should really be handled by a physics engine instead. 
}
