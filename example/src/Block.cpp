#include "../include/Block.hpp"
#include "../../include/components/CollisionObject.hpp"
#include "../../include/components/GameObject.hpp"
#include "../../include/components/ComponentUtils.hpp"
#include "../../include/core/EventSystem/SignalEmitter.hpp"
#include "../../include/core/EventSystem/Signal.hpp"
#include "../../include/core/EventSystem/EventHandler.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include <fstream>
#include <string>

std::ofstream block_debug_log("debug_log.txt", std::ios::app);

Block::Block() : CollisionObject()
{
	block_debug_log << "entered block constructor" << std::endl;

	this->sprites.push_back(new std::vector<std::string>({
		"OOO",
		"OOO"
	}));

	this->currentSprite = sprites[0];
	this->size = {3, 1};
	

	block_debug_log << "exited block constructor" << std::endl;
}

void Block::init()
{
	std::shared_ptr<Signal> test_signal = std::make_shared<Signal>();
	m_test_signal_emitter = create_signal_emitter(test_signal, "TEST_SIGNAL");
}

void Block::physicsProcess(double delta)
{
	applyGravity(this, delta);

	if (position.y > 30) 
	{
		block_debug_log << "firing signal from block" << std::endl;
		m_test_signal_emitter->emit();
	}
}

std::vector<std::string> Block::getVisual()
{
	return *currentSprite;
}