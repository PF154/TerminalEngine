#include <physics/PhysicsEngine.hpp>
#include <components/GameObject.hpp>
#include <ComponentUtils.hpp>

#include <vector>
#include <memory>

void PhysicsEngine::processGameObjects(std::vector<std::shared_ptr<GameObject>>& game_objects)
{
	for (std::shared_ptr<GameObject> obj : game_objects)
	{
		std::shared_ptr<PhysicsBody> physics_body = obj->get_physics_body();
		if (physics_body)
		{
			// Do something... what do we want to do?
			// The physics body should have a collider. We can use this to detect what it should be colliding with
			// So on every frame, we run
			std::vector<std::shared_ptr<GameObject>> collisions = physics_body->get_area()->get_last_frame_intersections();

			// I think we want each physics body to store things like: new_speed, new_pos, new_velocity, etc
			// So that we can calculate everything as they are, and then update
			for (std::shared_ptr<GameObject> collide_obj : collisions)
			{
				std::shared_ptr<PhysicsBody> collide_obj_physics_body = obj->get_physics_body();
				if (collide_obj_physics_body)
				{
					// New velocity should be the sum of all the velocities currently affecting the object?

					physics_body->new_vel = Velocity{0,0};
				}
			}
		}
	}
}