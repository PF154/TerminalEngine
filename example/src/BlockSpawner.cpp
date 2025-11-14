#include "../include/BlockSpawner.hpp"
#include "../include/Block.hpp"

#include <components/ComponentUtils.hpp>

#include <fstream>
#include <random>
#include <chrono>


std::ofstream spawner_debug_log("block_debug.txt", std::ios::app);

BlockSpawner::BlockSpawner() : GameObject()
{

}

void BlockSpawner::setup()
{
	std::shared_ptr<Timer> timer = create_new_timer();
	timer->repeat = true;
	timer->set_duration(std::chrono::seconds(2));

	create_signal_catcher(timer->get_socket_id(), [this]() { spawn_new_block(); });
}

void BlockSpawner::spawn_new_block()
{
	Position new_block_pos = Position{double((rand() % 40) + 4), 4.0};

	std::shared_ptr<Block> block = initstate_game_object<Block>();

	block->set_transform_position(new_block_pos);
}