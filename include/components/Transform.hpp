#pragma once

#include <components/ComponentUtils.hpp>

struct Transform
{
	Size size = {0, 0};
	Position position = {0.0, 0.0};
	Scale scale = {1, 1};
	Velocity velocity = {0.0, 0.0};

	void set_position(Position new_pos) { position = new_pos; }
};