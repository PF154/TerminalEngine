#pragma once

#include <components/GameObject.hpp>
#include <core/EventSystem/SignalCatcher.hpp>
#include <utils/Timer.hpp>

#include <memory>
#include <random>

class BlockSpawner : public GameObject
{
	public:
		BlockSpawner();
		virtual ~BlockSpawner() = default;

		void setup() override;
	private:

		void spawn_new_block();
};