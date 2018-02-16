#pragma once

class Sprite
{
public:
	Sprite(bool anim);
	~Sprite() = default;
private:
	bool animated = false;

};