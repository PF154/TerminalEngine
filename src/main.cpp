#include <iostream>
#include <memory>

#include <core/Engine.hpp>
#include <core/Game.hpp>
#include <core/Scene.hpp>

std::shared_ptr<Game> createTestGame()
{
	std::shared_ptr<Game> testGame = std::make_shared<Game>();
	std::shared_ptr<Scene> testScene = std::make_shared<Scene>();

	// Block* block = new Block(testGame);
	// block->position = Position{4, 4};

	// testScene->addEntity(block);

	testGame->setStartScene(testScene);

	return testGame;
}

int main()
{

	// Create instance of engine and run it.
	Engine engine;
	std::shared_ptr<Game> testGame = createTestGame();
	engine.setGame(testGame);

	engine.run();

	return 0;
}