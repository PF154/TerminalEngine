#include "../../../include/core/EventSystem/SignalCatcher.hpp"

void SignalCatcher::attempt_catch()
{
	if (!m_event_handler) 
	{
		std::cout << "Attempted to catch a signal through a catcher with no event handler reference, unsuccessful" << std::endl;
		return;
	}
	if (!m_catch_function)
	{
		std::cout << "Attempted to catch a signal without setting a catch function. Proceeding, but nothing will be called" << std::endl;
	}

	std::shared_ptr<Signal> recieved_signal = m_event_handler->retrieve_socket(m_event_socket_name);
	if (recieved_signal)
	{
		if (m_catch_function)
		{
			m_catch_function();
		}
	}
}