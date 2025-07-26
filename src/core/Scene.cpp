#include "../../include/core/Scene.hpp"
#include "../../include/components/GameObject.hpp"
#include "../../example/include/Block.hpp"

#include <vector>

Scene::Scene()
{
	// GameObject* dummyObject = new GameObject();
	// addEntity(dummyObject);

	// Block* block = new Block();
	std::shared_ptr<Block> block = std::make_shared<Block>();

	block->position = Position{4, 4};

	addEntity(block);
}