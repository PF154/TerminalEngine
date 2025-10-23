#pragma once

#include <components/GameObject.hpp>
#include <components/PhysicsBody.hpp>
#include <components/ComponentUtils.hpp>

#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>
#include <cmath>

struct Collision
{
	// Should keep in mind that the collision normal should always be standardized
	// to be in the direction of either obj_1 or obj_2 across the entire codebase
	std::shared_ptr<GameObject> obj_1;
	std::shared_ptr<GameObject> obj_2;
	Vec collision_normal;
};

// I think it makes most sense for this to just be a namespace.
// Having a PhysicsEngine class feels like a needless abstraction at this point,
// since really all we are storing here is a single function call, however I would
// like to indicate that the function is specifically for Physics
namespace Physics
{
	// Ideally we should be passing game_objects by reference
	void processExternalForces(const std::vector<std::shared_ptr<GameObject>>& game_objects, double delta)
	{	
		// Gravity
		const double gravity = 9.8;

		// This is kind of a stupid way to do this... why are we calling into physics just to call back into GameObject?
		// For now though, it's fine
		for (std::shared_ptr<GameObject> obj : game_objects)
		{
			if (!obj->get_physics_body().has_value()) continue;
			obj->applyGravity(delta);
		}
	}

	void processCollisions(std::vector<std::shared_ptr<GameObject>>& game_objects)
	{
		std::vector<Collision> collisions;

		// Using index-based for loops here because it's easier to filter out objects that have already been processed
		for (int i=0; i < game_objects.size(); i++)
		{
			// I'm tempted to reset the gameobject new_vel to 0 here, but I'm wondering if that should be
			// handled in some sort of physics_init funciton. I don't know if there will be any other influences
			// other than collisions. I guess there kind of will be because of potential gravity, but it's a question
			// of what order we want things to act in.
			// For now, new_vel reset will be handled in a different function, possibly with some other setup stuff.

			// Really, there's some restructuring that needs to happen here.
			// An area should not be an independent entity on an object if it's going to be detecting physics collisions
			// The PhysicsBody should own the area.

			// So the following change should be made

			std::shared_ptr<GameObject> obj = game_objects[i];
			// std::shared_ptr<Area> area = obj->get_area();
			// if (!area) continue;

			if (!obj->get_physics_body().has_value()) continue;
			std::shared_ptr<PhysicsBody> phys_bod = obj->get_physics_body().value();

			std::shared_ptr<Area> area = phys_bod->get_physics_area(); // Feel like get_area should be protected and this should be friend func to access it
			if (!area) continue;

			// This is O(n^2) at this point, which isn't great, but I can't imagine
			// that we are going to deal with enough objects for that to ever be an issue.
			// If it is, we can implement bounding box tree or other.
			for (int j=i+1; j < game_objects.size(); j++)
			{
				std::shared_ptr<GameObject> other = game_objects[j];

				if (!other->get_physics_body().has_value()) continue;
				std::shared_ptr<PhysicsBody> other_phys_bod = other->get_physics_body().value();
				std::shared_ptr<Area> other_area = phys_bod->get_physics_area();
				if (!other_area) continue;
				// Check if other and obj collide. If they do, add the collision to the map
				
				std::optional<Vec> collision_norm = area->overlaps_with(other_area);

				if (collision_norm.has_value()) 
				{
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

			obj_1_body->contribute_to_next_frame_impulse(Vec{impulse * collision.collision_normal.x, impulse * collision.collision_normal.y});
			obj_2_body->contribute_to_next_frame_impulse(Vec{-1.0 * impulse * collision.collision_normal.x, -1.0 * impulse * collision.collision_normal.y});
		}
	}

};

// Potential code restructure:
// Have a struct called CollisionData
// struct stores a pointer to the colliding objects
// struct also stores the collision normal
// We then iterate through CollisionData objects, and instead of summing velocities
// in the engine, we just sum them on the physics bodies
// On all physicsbodies, new_vel is then reset every tick to 0