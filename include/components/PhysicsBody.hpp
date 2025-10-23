#pragma once

#include <components/ComponentUtils.hpp>
#include <components/Area.hpp>

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

		Velocity vel;

		PhysicsBodyType get_body_type() { return m_body_type; }

		const std::shared_ptr<Area> get_physics_area() { return m_physics_area; }

		const double get_mass() { return m_mass; }

		void contribute_to_next_frame_impulse(Vec impulse) 
		{ 
			m_next_frame_impulse.x += impulse.x; 
			m_next_frame_impulse.y += impulse.y; 
		}



	private:
		// std::shared_ptr<Area> m_area;

		double m_mass = 1.0;
		// float elasticity = ?
		// other stuff can go here too 
		std::shared_ptr<Area> m_physics_area;

		PhysicsBodyType m_body_type;

		// We can decide what to do with this based on type
		// I.e. Kinematic and Static should probably ignore it
		// Dynamic should update velocity from it on some kind of update call
		Vec m_next_frame_impulse = Vec{0, 0};
};