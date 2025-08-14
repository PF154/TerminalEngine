#pragma once

#include "EventHandler.hpp"
#include "Signal.hpp"

#include <memory>
#include <string>

// Emitters can be added to an object to interact with the scene's event handler

class SignalEmitter
{
	public:
		SignalEmitter() {};
		SignalEmitter(std::shared_ptr<EventHandler> event_handler, std::string socket_name);

		void set_signal(std::shared_ptr<Signal> signal)
		{
			m_signal = signal;
		}

		void emit()
		{
			m_event_handler->populate_socket(m_destination_socket_name, m_signal);
		}

	private:
		std::shared_ptr<EventHandler> m_event_handler;
		std::shared_ptr<Signal> m_signal;
		std::string m_destination_socket_name;
};