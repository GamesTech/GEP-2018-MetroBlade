#include "pch.h"
#include "GameComponent.h"

std::string GameComponent::getTag() const
{
	return tag;
}

void GameComponent::setTag(std::string new_tag)
{
	tag = new_tag;
}
