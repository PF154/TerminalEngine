#include <core/Scene.hpp>
#include <components/GameObject.hpp>
#include "../../example/include/Block.hpp"
#include "../../example/include/CatcherTest.hpp"
#include <core/EventSystem/EventHandler.hpp>
#include <core/SceneData.hpp>

#include <vector>
#include <memory>
#include <type_traits>
#include <iostream>

#include <fstream>

std::ofstream scene_debug_log("debug_log.txt", std::ios::app);

Scene::Scene()
{
	m_scene_data = std::make_shared<SceneData>();

	scene_debug_log << "entered scene constructor" << std::endl;
	// SceneData MUST be set before any objects are added to the scene
	// GameObjects depend on SceneData if they have emitters or recievers
	m_event_handler = std::make_shared<EventHandler>();

	scene_debug_log << "created event handler" << std::endl;

	m_scene_data->set_event_handler(m_event_handler);

	scene_debug_log << "created event handler and scene data" << std::endl;


	// GameObject* dummyObject = new GameObject();
	// addEntity(dummyObject);

	// Block* block = new Block();
	// std::shared_ptr<Block> block = std::make_shared<Block>();

	// addEntity(block);

	// std::shared_ptr<CatcherTest> testCatcher = std::make_shared<CatcherTest>();

	// addEntity(testCatcher);

	std::shared_ptr<Block> block = instantiateEntity<Block>();

	std::shared_ptr<CatcherTest> testCatcher = instantiateEntity<CatcherTest>();
}

void Scene::addEntity(std::shared_ptr<GameObject> gameObject) 
{
	// We don't want to have to initiate all of the event handler/scene data stuff on the user end
	// Unless that is, we have some sort of createGameObject function, which is something to explore
	// But anyway, here is where we want to make sure that all the member variables of the gameObject are set
	gameObject->set_scene_data(m_scene_data);

	m_game_objects.push_back(gameObject);
};

template <typename T>
std::shared_ptr<T> Scene::instantiateEntity()
{
	// We want to make sure that we are actually working with a GameObject before calling things like set_scene_data()
	static_assert(std::is_base_of<GameObject, T>::value, "Error: Attempted to call instatiateEntity on a class not derived from GameObjeect.");

	std::shared_ptr<T> new_entity = std::make_shared<T>();

	// do some stuff to configure the entity/send it to other objects
	new_entity->set_scene_data(m_scene_data);
	m_game_objects.push_back(new_entity);

	return new_entity;
}