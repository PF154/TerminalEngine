#pragma once

#include "GameObject.hpp"
#include "ComponentUtils.hpp"

#include <vector>
#include <string>

class VisualObject : public GameObject
{
	public:
		VisualObject();
		virtual ~VisualObject() = default;

		// Constructor to be used when converting from gameObject
		VisualObject(Position position, Velocity velocity);


		// VisualObject(Game* game);

		virtual std::vector<std::string> getVisual() { return visualRep; };
		inline Size getSize() { return size; };
		inline Position getPosition() { return position; };

	private:
		std::vector<std::string> visualRep;
};