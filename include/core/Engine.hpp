#pragma once

#include <components/Viewport.hpp>
#include <core/Game.hpp>
#include <core/Scene.hpp>

#include <vector>
#include <memory>

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

		inline void setGame(std::shared_ptr<Game> game) { this->m_game = std::move(game); };
	private:
		void begin();
		void update(double delta);
		void graphicsUpdate(double delta);
		void physicsUpdate(double delta);
		void loadNewScene(std::shared_ptr<Scene> new_scene);

		// At the moment these are shared pointers. I feel like I can at least make m_current_scene unique, but this is faster to test with
		std::shared_ptr<Game> m_game;
		std::shared_ptr<Scene> m_current_scene;

		Viewport m_viewport;

		int m_tick_rate = 30; // Ticks per second

		// Essential Functions
		// void createInstance(GameObject* object);
};
