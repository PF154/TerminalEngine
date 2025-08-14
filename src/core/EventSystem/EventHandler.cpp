#include "../../../include/core/EventSystem/EventHandler.hpp"
#include "../../../include/core/EventSystem/Signal.hpp"

#include <memory>
#include <string>

std::string EventHandler::generate_unique_name()
{
	return std::to_string(next_unique_id++);
}

std::shared_ptr<Signal> EventHandler::retrieve_socket(std::string socket_name)
{
	if (signal_map[socket_name]) return signal_map[socket_name];
	return nullptr;
}

void EventHandler::populate_socket(std::string socket_name, std::shared_ptr<Signal> signal)
{
	// Really, there should be some checks here to see if the socket actually exists...
	// If we want to introduce a queue system for each socket, here is where to do it
	signal_map[socket_name] = signal;
}