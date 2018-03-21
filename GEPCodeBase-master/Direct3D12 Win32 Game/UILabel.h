// Date - 19/03/18
// author - Nathan Butt	


#pragma once

#include "UIObject.h"

class UILabel : public UIObject 
{
public:
	UILabel() = default;
	~UILabel() = default;

	void setText(std::string new_text);

	virtual void Tick(GameStateData * _GSD) override;
	virtual void Render(RenderData * _RD) override;

	void setTextColour(Vector4   new_colour);

private:
	std::wstring text;
	Vector4  colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	
	// TODO - Add the ability to add a custom font.
};