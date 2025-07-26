#include "../../include/components/GameObject.hpp"

#include <iostream>
#include <format>

// GameObject::GameObject(Game* game) : game(game)
// {

// }

void GameObject::update(double delta)
{
	process(delta);
	physicsProcess(delta);
}

void GameObject::process(double delta)
{

}

void GameObject::physicsProcess(double delta)
{
	
}

void GameObject::applyGravity(GameObject* object, double delta)
{
	// std::cout << "Appling Gravity _____________________________________________________________________________" << std::endl;
	object->velocity.y += 75.0;
	object->position.y += object->velocity.y * delta;
}