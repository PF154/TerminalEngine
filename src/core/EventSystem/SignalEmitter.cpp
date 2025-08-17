#include <core/EventSystem/SignalEmitter.hpp>
#include <core/EventSystem/EventHandler.hpp>

#include <memory>
#include <string>

SignalEmitter::SignalEmitter(std::shared_ptr<EventHandler> event_handler, std::string socket_name)
{
	m_event_handler = event_handler;
	m_destination_socket_name = socket_name;
	m_event_handler->verify_socket(socket_name);
}