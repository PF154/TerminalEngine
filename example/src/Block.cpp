#include "../include/Block.hpp"
#include "../../include/components/CollisionObject.hpp"
#include "../../include/components/GameObject.hpp"
#include "../../include/components/ComponentUtils.hpp"

#include <vector>
#include <string>
#include <iostream>

Block::Block() : CollisionObject()
{
	this->sprites.push_back(new std::vector<std::string>({
		"OOO",
		"OOO"
	}));

	this->currentSprite = sprites[0];
	this->size = {3, 1};
}

void Block::physicsProcess(double delta)
{
	applyGravity(this, delta);
}

std::vector<std::string> Block::getVisual()
{
	return *currentSprite;
}