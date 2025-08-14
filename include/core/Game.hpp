#pragma once

// #include "Scene.hpp"

#include <vector>
#include <memory>

class Scene;

// The game stores the entity list and game object for a specific game
// A Game object should be a member of the Engine class upon startup

// This is the base class for every game made with TerminalHero
// For instance, you would have something like "class TetrisGame : public Game"
// Upon startup, a derived class would add the necessary things to its entityList in an overridden constuctor.

class Game
{
	public:
		void play();

		inline void setStartScene(std::shared_ptr<Scene> scene) { startScene = scene; };

		std::shared_ptr<Scene> getCurrentScene() { return currentScene; };

		const double GRAVITY = 5.0;
	private:
		std::shared_ptr<Scene> currentScene;
		std::shared_ptr<Scene> startScene;
};