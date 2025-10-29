#include "../include/StaticBlock.hpp"
#include <components/GameObject.hpp>
#include <components/ComponentUtils.hpp>
#include <core/EventSystem/SignalEmitter.hpp>
#include <core/EventSystem/Signal.hpp>
#include <core/EventSystem/EventHandler.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include <fstream>
#include <string>

std::ofstream StaticBlock_debug_log("block_debug_log.txt", std::ios::app);

StaticBlock::StaticBlock() : GameObject()
{

}

void StaticBlock::setup()
{
	// Add transform
	Transform t;
	t.position = Position{10, 20};
	t.size = Size{12, 1};
	add_transform(std::move(t));

	// Add mesh
	StaticMesh sm;
	sm.set_sprite(std::vector<std::string>({
		"HHHHHHHHHHH",
		"HHHHHHHHHHH"
	}));
	sm.set_size(Size{11, 1});
	add_static_mesh(std::move(sm));

	// Add physics body
	PhysicsBody pb;
	pb.set_body_type(PhysicsBodyType::STATIC);
	add_physics_body(std::move(pb));

	if (m_physics_body.has_value()) StaticBlock_debug_log << "StaticBlock has physics body" << std::endl;

	StaticBlock_debug_log << "completed StaticBlock setup" << std::endl;
}

void StaticBlock::init()
{
	
}

void StaticBlock::physicsProcess(double delta)
{
}