// Kind of bad practice, but I'm keeping relative paths for example objects
// Eventually these should be compiled some way with CMake to avoid this
// Maybe we put that on the user, maybe we find a way to streamline it, idk

#include "../include/Block.hpp"
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

std::ofstream block_debug_log("block_debug_log.txt", std::ios::app);

Block::Block() : GameObject()
{

}

void Block::setup()
{
	// Add transform
	Transform t;
	t.position = Position{4, 4};
	t.size = Size{3, 1};
	add_transform(std::move(t));

	// Add mesh
	StaticMesh sm;
	sm.set_sprite(std::vector<std::string>({
		"OOO",
		"OOO"
	}));
	sm.set_size(Size{2, 1});
	add_static_mesh(std::move(sm));

	// Add physics body
	PhysicsBody pb;
	add_physics_body(std::move(pb));

	// Create Signal emitter
	std::shared_ptr<Signal> test_signal = std::make_shared<Signal>();
	m_test_signal_emitter = create_signal_emitter(test_signal, "TEST_SIGNAL");

	if (m_physics_body.has_value()) block_debug_log << "Block has physics body" << std::endl;

	block_debug_log << "completed block setup" << std::endl;
}

void Block::init()
{
	
}

void Block::physicsProcess(double delta)
{	
	block_debug_log << "Block velocity: " << m_physics_body.value()->get_velocity().y << std::endl;

	if (get_transform().has_value() && get_transform().value().position.y > 60) 
	{
		// block_debug_log << "firing signal from block" << std::endl;
		// m_test_signal_emitter->emit();
		delete_self();
	}
}