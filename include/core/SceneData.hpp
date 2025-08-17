#pragma once

// Holds scene specific data, like event handlers etc.

#include <core/EventSystem/EventHandler.hpp>

#include <memory>

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

	private:
		std::shared_ptr<EventHandler> m_event_handler;
};