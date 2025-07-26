#pragma once

#include "../../include/components/CollisionObject.hpp"
#include "../../include/components/ComponentUtils.hpp"

#include <vector>
#include <string>

class Block : public CollisionObject
{
	public:
		Block();
		virtual ~Block() = default;

		std::vector<std::string> getVisual() override;
	private:
		void physicsProcess(double delta) override;

		std::vector<std::vector<std::string>*> sprites;
		std::vector<std::string>* currentSprite;
};