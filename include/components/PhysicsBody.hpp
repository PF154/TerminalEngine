#pragma once

#include <components/ComponentUtils.hpp>

#include <memory>

enum PhysicsBodyType
{
	STATIC,
	DYNAMIC,
	KINEMATIC
};

class PhysicsBody
{
	public:
		// std::shared_ptr<Area> get_area() {};

		Position new_pos;
		Velocity new_vel;

	private:
		// std::shared_ptr<Area> m_area;

		float mass = 1.0f;
		// float elasticity = ?
		// other stuff can go here too 

		PhysicsBodyType body_type;
};