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
	void updatePhysicsObjects(const std::vector<std::shared_ptr<GameObject>>& game_objects, double delta);
	// Ideally we should be passing game_objects by reference
	void processExternalForces(const std::vector<std::shared_ptr<GameObject>>& game_objects, double delta);

	void processCollisions(const std::vector<std::shared_ptr<GameObject>>& game_objects);

};