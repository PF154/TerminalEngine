#pragma once

#include <components/ComponentUtils.hpp>
#include <components/Mesh.hpp>
#include <components/StaticMesh.hpp>
#include <components/AnimMesh.hpp>
#include <components/Transform.hpp>
#include <components/Collider.hpp>
#include <components/PhysicsBody.hpp>
#include <core/SceneData.hpp>
#include <core/EventSystem/SignalEmitter.hpp>
#include <core/EventSystem/SignalCatcher.hpp>
#include <core/EventSystem/Signal.hpp>
#include <core/EventSystem/EventHandler.hpp>
#include <utils/Timer.hpp>

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <type_traits>

class GameObject
{
	public:
		// Default constructor/destructor
		GameObject() {};
		virtual ~GameObject() = default;

		void update(double delta);

		void set_scene_data(std::shared_ptr<SceneData> scene_data)
		{
			m_scene_data = scene_data;
		}


		// This function is for the user to define the object. It is where we add components, set
		// position, etc.
		virtual void setup() {};

		// This function is for game logic stuff that needs to occur after the object has been constructed
		// I believe that this will be a function the user overrides eventually
		// At the moment it handles the following expanded list of stuff
		virtual void init() {};
		
		// Renderer should call this every frame. The engine will look to see if it got something,
		// and if it did, it will render it. I think this simplifys things, becuase otherwise we
		// have some redundant call like "if (gameObject->has_mesh())". Whereas here we can do
		// std::shared_ptr<Mesh> obj_mesh = gameObject->get_mesh(); if (obj_mesh) {//render code}
		std::shared_ptr<Mesh> get_mesh() { return m_mesh; };
		std::shared_ptr<Collider> get_collider() { return m_collider; };
		std::shared_ptr<Transform> get_transform() { return m_transform; };
		std::shared_ptr<PhysicsBody> get_physics_body() { return m_physics_body; }

		// Other functions that will be useful
		Position get_position(); 


		// The following setup functions will be used by the end-user for object definition
		void add_satic_mesh();
		void add_static_mesh(std::shared_ptr<StaticMesh> new_mesh);

		void replace_mesh_with_static();
		void replace_mesh_with_static(std::shared_ptr<StaticMesh> new_mesh);

		void add_anim_mesh();
		void add_anim_mesh(std::shared_ptr<AnimMesh> new_mesh);

		void replace_mesh_with_anim();
		void replace_mesh_with_anim(std::shared_ptr<AnimMesh> new_mesh);

		// If the user opts for one of the argument-less functions, we need some way for them to still set the values
		void add_transform();
		void add_transform(std::shared_ptr<Transform> new_trans);


		
	protected:

		virtual void process(double delta);
		virtual void physicsProcess(double delta);

		void applyGravity(GameObject& object, double delta);

		std::shared_ptr<SignalEmitter> create_signal_emitter(std::shared_ptr<Signal> signal, std::string socket_name);

		void create_signal_catcher(std::string socket_name, std::function<void()> catch_function);

		std::shared_ptr<Timer> create_new_timer();

		template <typename T>
		std::shared_ptr<T> initstate_game_object()
		{
			std::shared_ptr<T> new_entity = std::make_shared<T>();

			std::shared_ptr<GameObject> game_object_ptr = std::dynamic_pointer_cast<GameObject>(new_entity);
			if (game_object_ptr)
			{
				game_object_ptr->set_scene_data(m_scene_data);
			}
			else
			{
				std::cerr << "Attempted to instantiate a non-GameObject type, not possible" << std::endl;
				return nullptr;
			}

			m_scene_data->m_game_objects.push_back(new_entity);
			
			return new_entity;
		}

		std::shared_ptr<SceneData> m_scene_data;
		std::vector<std::shared_ptr<SignalCatcher>> m_signal_catchers;

		std::vector<std::shared_ptr<Timer>> m_timers;

		// Originally was going to do this as unordered map, but that seems needlessly complex
		// for this alternative which does all the same stuff.
		std::shared_ptr<Mesh> m_mesh = nullptr;
		std::shared_ptr<Collider> m_collider = nullptr;
		std::shared_ptr<Transform> m_transform = nullptr;
		std::shared_ptr<PhysicsBody> m_physics_body = nullptr;
};