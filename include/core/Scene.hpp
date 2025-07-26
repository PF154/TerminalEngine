#pragma once

#include <vector>
#include <iostream>
#include <memory>

class GameObject;

class Scene
{
	public:
		Scene();

		// This list should be continually sorted by z-depth
		// std::vector<GameObject*> getGameObjects() {
		std::vector<std::shared_ptr<GameObject>> getGameObjects() {

			// std::cout << "getGameObjects called on " << static_cast<const void*>(this) << std::endl;
			return this->gameObjects; 
			};

		// inline void addEntity(GameObject* gameObject) { gameObjects.push_back(gameObject); };
		inline void addEntity(std::shared_ptr<GameObject> gameObject) { gameObjects.push_back(gameObject); };

		const double GRAVITY = 5.0;
	private:
		// std::vector<GameObject*> gameObjects;
		std::vector<std::shared_ptr<GameObject>> gameObjects;
};