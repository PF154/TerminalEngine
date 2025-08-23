#include "../include/BlockSpawner.hpp"
#include "../include/Block.hpp"

#include <components/ComponentUtils.hpp>

#include <fstream>
#include <random>

std::ofstream spawner_debug_log("block_debug.txt", std::ios::app);

BlockSpawner::BlockSpawner() : GameObject()
{

}

void BlockSpawner::setup()
{
	std::shared_ptr<Timer> timer = create_new_timer();
	timer->repeat = true;

	spawner_debug_log << "created timer for socket " << timer->get_socket_id() << std::endl;
	spawner_debug_log << "Block spawner contains " << m_timers.size() << " timers" << std::endl;

	create_signal_catcher(timer->get_socket_id(), [this]() { spawn_new_block(); });

	spawner_debug_log << "created block spawner" << std::endl;
}

void BlockSpawner::spawn_new_block()
{
	Position new_block_pos = Position{double((rand() % 25) + 4), 4.0};

	std::shared_ptr<Block> block = initstate_game_object<Block>();

	spawner_debug_log << "created object for a new block" << std::endl;

	block->setup();
	block->init();

	if (!block->get_transform()) spawner_debug_log << "no transform!" << std::endl;

	block->get_transform()->position = new_block_pos;


	spawner_debug_log << "Spawn a new block!" << std::endl;
}