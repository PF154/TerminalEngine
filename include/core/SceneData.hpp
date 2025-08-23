#pragma once

// Holds scene specific data, like event handlers etc.

#include <core/EventSystem/EventHandler.hpp>

#include <memory>
#include <functional>
#include <vector>
#include <string>

class GameObject;

class SceneData
{
	public:
		std::shared_ptr<EventHandler> get_event_handler()
		{
			return m_event_handler;
		}

		void set_event_handler(std::shared_ptr<EventHandler> event_handler)
		{
			m_event_handler = event_handler;
		}

		std::vector<std::shared_ptr<GameObject>> m_game_objects;

		std::string make_unique_timer_socket_id()
		{
			return std::string("TIMER_") + std::to_string(last_timer_id++);
		}

	private:
		std::shared_ptr<EventHandler> m_event_handler;

		int last_timer_id = 0;
};