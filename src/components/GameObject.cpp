#include "../../include/components/GameObject.hpp"
#include "../../include/core/EventSystem/Signal.hpp"
#include "../../include/core/EventSystem/SignalEmitter.hpp"
#include "../../include/core/EventSystem/SignalCatcher.hpp"

#include <iostream>
#include <format>
#include <memory>

// TODO: Make sure that there are checks for value overflow on any transform parameter or
// param that may change

void GameObject::update(double delta)
{
	// Check signal catcher
	for (std::shared_ptr<SignalCatcher> catcher : m_signal_catchers)
	{
		catcher->attempt_catch();
	}

	process(delta);
	physicsProcess(delta);
}

void GameObject::process(double delta)
{

}

void GameObject::physicsProcess(double delta)
{
	
}

void GameObject::applyGravity(GameObject* object, double delta)
{
	// std::cout << "Appling Gravity _____________________________________________________________________________" << std::endl;
	object->velocity.y += 75.0;
	object->position.y += object->velocity.y * delta;
}

std::shared_ptr<SignalEmitter> GameObject::create_signal_emitter(std::shared_ptr<Signal> signal, std::string socket_name)
{
	if (!m_scene_data)
	{
		std::cout << "Attempted to create a signal emitter for an object with a null SceneData reference, aborting" << std::endl;
		return nullptr;
	}
	if (!m_scene_data->get_event_handler())
	{
		std::cout << "Attempted to create a signal emitter for an object whose SceneData has a null EventHandler, aborting" << std::endl;
		return nullptr;
	}

	std::shared_ptr emitter = std::make_shared<SignalEmitter>(m_scene_data->get_event_handler(), socket_name);
	emitter->set_signal(signal);
	return emitter;
}

void GameObject::create_signal_catcher(std::string socket_name, std::function<void()> catch_function)
{
	if (!m_scene_data)
	{
		std::cout << "Attempted to create a signal catcher for an object with a null SceneData reference, aborting" << std::endl;
	}
	if (!m_scene_data->get_event_handler())
	{
		std::cout << "Attempted to create a signal catcher for an object whose SceneData has a null EventHandler, aborting" << std::endl;
	}

	// This is incorrect. The type input for the first template should be SignalCatcher<OwnerType>, I think
	m_signal_catchers.push_back(std::make_shared<SignalCatcher>(
		m_scene_data->get_event_handler(),
		socket_name,
		catch_function)
	);
}