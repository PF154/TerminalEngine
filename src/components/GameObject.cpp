#include <components/GameObject.hpp>
#include <core/EventSystem/Signal.hpp>
#include <core/EventSystem/SignalEmitter.hpp>
#include <core/EventSystem/SignalCatcher.hpp>

#include <components/StaticMesh.hpp>
#include <components/AnimMesh.hpp>
#include <components/Transform.hpp>

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

void GameObject::applyGravity(GameObject& object, double delta)
{
	// std::cout << "Appling Gravity _____________________________________________________________________________" << std::endl;
	std::shared_ptr<Transform> obj_trans = object.get_transform();
	obj_trans->velocity.y += 75.0;
	obj_trans->position.y += obj_trans->velocity.y * delta;
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

void GameObject::add_satic_mesh()
{
	if (m_mesh)
	{
		std::cout << "Attempted ot add static mesh to object with existing mesh object; did you mean to use replace_mesh_with_static?" << std::endl;
		return;
	}

	m_mesh = std::make_shared<StaticMesh>();
}

void GameObject::add_static_mesh(std::shared_ptr<StaticMesh> new_mesh)
{
	if (m_mesh)
	{
		std::cout << "Attempted ot add static mesh to object with existing mesh object; did you mean to use replace_mesh_with_static?" << std::endl;
		return;
	}

	m_mesh = new_mesh;
}

void GameObject::replace_mesh_with_static()
{
	m_mesh = std::make_shared<StaticMesh>();
}

void GameObject::replace_mesh_with_static(std::shared_ptr<StaticMesh> new_mesh)
{
	m_mesh = new_mesh;
}

void GameObject::add_anim_mesh()
{
	if (m_mesh)
	{
		std::cout << "Attempted to add anim mesh to object with existing mesh object; did you mean to use replace_mesh_with_anim?" << std::endl;
		return;
	}

	m_mesh = std::make_shared<AnimMesh>();
}

void GameObject::add_anim_mesh(std::shared_ptr<AnimMesh> new_mesh)
{
	if (m_mesh)
	{
		std::cout << "Attempted to add anim mesh to object with existing mesh object; did you mean to use replace_mesh_with_anim?" << std::endl;
		return;
	}

	m_mesh = new_mesh;
}

void GameObject::replace_mesh_with_anim()
{
	m_mesh = std::make_shared<AnimMesh>();
}

void GameObject::replace_mesh_with_anim(std::shared_ptr<AnimMesh> new_mesh)
{
	m_mesh = new_mesh;
}

void GameObject::add_transform()
{
	if (m_transform)
	{
		std::cout << "Attempted to add transform to object with existing transform component" << std::endl;
		return;
	}

	m_transform = std::make_shared<Transform>();
}

void GameObject::add_transform(std::shared_ptr<Transform> new_trans)
{
	if (m_transform)
	{
		std::cout << "Attempted to add transform to object with existing transform component" << std::endl;
		return;
	}

	m_transform = new_trans;
}

Position GameObject::get_position()
{
	if (!m_transform)
	{
		std::cerr << "Attempted to get position, but object has no transform" << std::endl;
		return Position{0, 0, false};
	}
	return m_transform->position;
}