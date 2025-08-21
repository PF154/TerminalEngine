#pragma once

#include <core/EventSystem/EventHandler.hpp>
#include <core/SceneData.hpp>

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
			return this->m_game_objects; 
			};

		// inline void addEntity(GameObject* gameObject) { gameObjects.push_back(gameObject); };
		void addEntity(std::shared_ptr<GameObject> gameObject);

		// This should probably replace the addEntity function eventually
		template <typename T>
		std::shared_ptr<T> instantiateEntity();

		template <typename T>
		std::shared_ptr<T> createEntity();

		const double GRAVITY = 5.0;
	private:
		// std::vector<GameObject*> gameObjects;
		std::vector<std::shared_ptr<GameObject>> m_game_objects;

		std::shared_ptr<SceneData> m_scene_data;

		std::shared_ptr<EventHandler> m_event_handler;
};