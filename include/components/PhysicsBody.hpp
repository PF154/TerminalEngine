#pragma once

#include <components/ComponentUtils.hpp>
#include <components/Area.hpp>

#include <memory>
#include <limits>

enum PhysicsBodyType
{
	STATIC,
	DYNAMIC,
	KINEMATIC
};

class PhysicsBody
{
	public:
		Velocity vel = {0.0, 0.0};

		void update(double delta)
		{
			if (m_body_type == PhysicsBodyType::DYNAMIC)
			{
				vel.x += m_next_frame_impulse.x / m_mass;
				vel.y += m_next_frame_impulse.y / m_mass;
			}

			m_next_frame_impulse.x = 0.0;
			m_next_frame_impulse.y = 0.0;
		}

		PhysicsBodyType get_body_type() { return m_body_type; }
		void set_body_type(PhysicsBodyType new_type) { 
			m_body_type = new_type; 

			if (m_body_type == PhysicsBodyType::STATIC)
			{
				m_mass = std::numeric_limits<double>::infinity();
			}

		}

		Velocity get_velocity() 
		{ 
			if (m_body_type == PhysicsBodyType::DYNAMIC)
				return vel; 
			else return {0.0, 0.0};
		}

		const std::shared_ptr<Area> get_physics_area() { return m_physics_area; }
		void set_physics_area(std::shared_ptr<Area> new_area) { m_physics_area = std::move(new_area); }

		const double get_mass() { return m_mass; }
		void set_mass(double new_mass)
		{
			if (m_body_type == PhysicsBodyType::STATIC)
			{
				// Can't give mass to static 
				return;
			}
			m_mass = new_mass;
		}

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

		PhysicsBodyType m_body_type = DYNAMIC;

		// We can decide what to do with this based on type
		// I.e. Kinematic and Static should probably ignore it
		// Dynamic should update velocity from it on some kind of update call
		Vec m_next_frame_impulse = Vec{0, 0};
};