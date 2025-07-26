#pragma once

#include "../components/Viewport.hpp"
#include "../core/Game.hpp"

#include <vector>

// What do we want here?
// Update function
//		This should run at some consistent tick.
//		It will call updates to everything, including physics

class Engine
{
	public:
		Engine();
		~Engine();
		void run();

		inline void setGame(Game* game) { this->game = game; };
	private:
		void begin();
		void update(double delta);
		void graphicsUpdate(double delta);

		Game* game;

		Viewport viewport;

		int tick_rate = 30; // Ticks per second

		// Essential Functions
		// void createInstance(GameObject* object);
};
