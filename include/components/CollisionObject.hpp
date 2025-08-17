#pragma once

#include <components/VisualObject.hpp>

class CollisionObject : public VisualObject
{
	public:
		CollisionObject();
		virtual ~CollisionObject() = default;

		// CollisionObject(Game* game);
};