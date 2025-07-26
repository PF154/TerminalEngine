#pragma once

#include "VisualObject.hpp"

class CollisionObject : public VisualObject
{
	public:
		CollisionObject();
		virtual ~CollisionObject() = default;

		// CollisionObject(Game* game);
};