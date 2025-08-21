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

std::ofstream block_debug_log("debug_log.txt", std::ios::app);

Block::Block() : GameObject()
{

}

void Block::setup()
{
	// Add transform
	add_transform();
	get_transform()->position = Position{4, 4};
	get_transform()->size = Size{3, 1};

	// Add mesh
	add_satic_mesh();
	get_mesh()->set_sprite(std::vector<std::string>({
		"OOO",
		"OOO"
	}));
	get_mesh()->set_size(Size{2, 1});

	// Create Signal emitter
	std::shared_ptr<Signal> test_signal = std::make_shared<Signal>();
	m_test_signal_emitter = create_signal_emitter(test_signal, "TEST_SIGNAL");

	block_debug_log << "completed block setup" << std::endl;
}

void Block::init()
{
	
}

void Block::physicsProcess(double delta)
{
	applyGravity(*this, delta);

	if (get_transform()->position.y > 30) 
	{
		block_debug_log << "firing signal from block" << std::endl;
		m_test_signal_emitter->emit();
	}
}