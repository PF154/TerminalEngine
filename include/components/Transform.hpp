#pragma once

#include <components/ComponentUtils.hpp>

struct Transform
{
	Size size;
	Position position;
	Scale scale;
	Velocity velocity = {0.0, 0.0};
};