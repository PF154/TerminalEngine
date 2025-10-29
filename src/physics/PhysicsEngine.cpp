#include <physics/PhysicsEngine.hpp>

#include <components/GameObject.hpp>
#include <components/PhysicsBody.hpp>
#include <components/ComponentUtils.hpp>

#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>
#include <cmath>
#include <fstream>

std::ofstream physics_debug_log("physics_debug.txt", std::ios::app);

void Physics::updatePhysicsObjects(const std::vector<std::shared_ptr<GameObject>>& game_objects, double delta)
{
	for (std::shared_ptr<GameObject> obj : game_objects)
	{
		if (!obj->get_physics_body().has_value()) continue;
		obj->get_physics_body().value()->get_physics_area()->origin = obj->get_transform().value().position;
	}
}

void Physics::processExternalForces(const std::vector<std::shared_ptr<GameObject>>& game_objects, double delta)
{	
	// Gravity
	const double gravity = 9.8;
	for (std::shared_ptr<GameObject> obj : game_objects)
	{
		if (!obj->get_physics_body().has_value()) continue;
		if (! (obj->get_physics_body().value()->get_body_type() == PhysicsBodyType::DYNAMIC)) continue;

		obj->get_physics_body().value()->vel.y += gravity * delta;
	}
}

void Physics::processCollisions(const std::vector<std::shared_ptr<GameObject>>& game_objects)
{
	// physics_debug_log << "processCollisions called" << std::endl;
	std::vector<Collision> collisions;

	// Using index-based for loops here because it's easier to filter out objects that have already been processed
	for (int i=0; i < game_objects.size(); i++)
	{
		std::shared_ptr<GameObject> obj = game_objects[i];

		if (!obj->get_physics_body().has_value()) continue;
		std::shared_ptr<PhysicsBody> phys_bod = obj->get_physics_body().value();

		std::shared_ptr<Area> area = phys_bod->get_physics_area(); // Feel like get_area should be protected and this should be friend func to access it
		if (!area) continue;

		// This is O(n^2) at this point, which isn't great, but I can't imagine
		// that we are going to deal with enough objects for that to ever be an issue.
		// If it is, we can implement bounding box tree or other.
		for (int j=i+1; j < game_objects.size(); j++)
		{
			// physics_debug_log << "iterating... j = " << j << std::endl;

			std::shared_ptr<GameObject> other = game_objects[j];

			if (!other->get_physics_body().has_value()) continue;

			// physics_debug_log << "Two objects with bodies found" << std::endl;
			// physics_debug_log << "Obj1 Addr: " << obj.get() << std::endl;
			// physics_debug_log << "Obj2 Addr: " << other.get() << std::endl;

			std::shared_ptr<PhysicsBody> other_phys_bod = other->get_physics_body().value();
			std::shared_ptr<Area> other_area = other_phys_bod->get_physics_area();
			if (!other_area) continue;
			// Check if other and obj collide. If they do, add the collision to the map

			// physics_debug_log << "Area1 Addr: " << area.get() << std::endl;
			// physics_debug_log << "Area2 Addr: " << other_area.get() << std::endl;
			
			std::optional<Vec> collision_norm = area->overlaps_with(other_area);

			if (collision_norm.has_value()) 
			{
				physics_debug_log << "Collision!" << std::endl;
				physics_debug_log << "Obj1 pos: " << obj->get_transform().value().position.x << ", " << obj->get_transform().value().position.y << std::endl;
				physics_debug_log << "Obj2 pos: " << other->get_transform().value().position.x << ", " << other->get_transform().value().position.y << std::endl;
				physics_debug_log << "Norm: " << collision_norm.value().x << ", " << collision_norm.value().y << std::endl;

				collisions.push_back(Collision{obj, other, collision_norm.value()});
			}
		}
	}

	for (Collision collision : collisions)
	{
		// Is there a possibility for a race condition here? Could something remove the physics body before we fully process the collision?
		std::shared_ptr<PhysicsBody> obj_1_body = collision.obj_1->get_physics_body().value();
		std::shared_ptr<PhysicsBody> obj_2_body = collision.obj_2->get_physics_body().value();

		Velocity obj_1_vel = obj_1_body->vel;
		Velocity obj_2_vel = obj_2_body->vel;

		double coll_dot = 	((obj_1_vel.x - obj_2_vel.x) * collision.collision_normal.x) + 
							((obj_1_vel.y - obj_2_vel.y) * collision.collision_normal.y);

		double e = 1.0;
		double impulse;

		if (std::isinf(obj_1_body->get_mass()) && std::isinf(obj_2_body->get_mass()))
		{
			// Can't calculate impluse for two static objects, just leave them be
			// Note: new_vel or impulse or whatever we are calling the update var in PhysicsBody should be 
			// an optional, because we want the option to not update it at all
			// We could also just default it to zero impulse, and that would do the same thing I guess
			continue;
		}

		double mass_term_1 = std::isinf(obj_1_body->get_mass()) ? 0 : (1 / obj_1_body->get_mass());
		double mass_term_2 = std::isinf(obj_2_body->get_mass()) ? 0 : (1 / obj_2_body->get_mass());
			
		impulse = ((1 + e) * coll_dot) / (mass_term_1 + mass_term_2);

		// physics_debug_log << "impulse: " << impulse << std::endl;

		obj_1_body->contribute_to_next_frame_impulse(Vec{-1.0 * impulse * collision.collision_normal.x, -1.0 * impulse * collision.collision_normal.y});
		obj_2_body->contribute_to_next_frame_impulse(Vec{impulse * collision.collision_normal.x, impulse * collision.collision_normal.y});
	}
}