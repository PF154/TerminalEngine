#pragma once

#include <components/ComponentUtils.hpp>
#include <core/SceneData.hpp>
#include <core/EventSystem/SignalEmitter.hpp>
#include <core/EventSystem/SignalCatcher.hpp>
#include <core/EventSystem/Signal.hpp>
#include <core/EventSystem/EventHandler.hpp>

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

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

		// This function is for game logic stuff that needs to occur after the object has been constructed
		// I believe that this will be a function the user overrides eventually
		// At the moment it handles the following expanded list of stuff
		virtual void init() {};

		Position position;
		Velocity velocity;
		Size size;

		// Originally was going to do this as unordered map, but that seems needlessly complex
		// for this alternative which does all the same stuff.


		
	protected:

		virtual void process(double delta);
		virtual void physicsProcess(double delta);

		void applyGravity(GameObject* object, double delta);

		std::shared_ptr<SignalEmitter> create_signal_emitter(std::shared_ptr<Signal> signal, std::string socket_name);

		void create_signal_catcher(std::string socket_name, std::function<void()> catch_function);

		std::shared_ptr<SceneData> m_scene_data;
		std::vector<std::shared_ptr<SignalCatcher>> m_signal_catchers;

		
};