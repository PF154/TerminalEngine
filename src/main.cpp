#include <iostream>

#include "../include/core/Engine.hpp"
#include "../include/core/Game.hpp"
#include "../include/core/Scene.hpp"
#include "../include/components/ComponentUtils.hpp"
#include "../example/include/Block.hpp"

Game* createTestGame()
{
	Game* testGame = new Game();
	Scene* testScene = new Scene();

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
	Game* testGame = createTestGame();
	engine.setGame(testGame);

	engine.run();

	return 0;
}