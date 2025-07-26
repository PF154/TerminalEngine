#include "../../include/components/VisualObject.hpp"
#include "../../include/components/GameObject.hpp"
#include "../../include/components/ComponentUtils.hpp"

VisualObject::VisualObject() : GameObject()
{
	
}

VisualObject::VisualObject(Position position, Velocity velocity)
{
	this->position = position;
	this->velocity = velocity;
}