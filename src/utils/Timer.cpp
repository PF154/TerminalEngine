#include <chrono>
#include <string>
#include <core/EventSystem/SignalEmitter.hpp>
#include <core/EventSystem/EventHandler.hpp>

#include <fstream>

#include <utils/Timer.hpp>

std::ofstream timer_debug_log("block_debug.txt", std::ios::app);

Timer::Timer (std::string socket_id, std::shared_ptr<EventHandler> event_handler)
{
	// When we create a timer, we want to:
	// Initialize it with a unique socket_id
	m_socket_id = socket_id;
	// Hook it up to the event system

	finish_emitter = SignalEmitter(event_handler, socket_id);
	std::shared_ptr<Signal> timer_signal = std::make_shared<Signal>();
	finish_emitter.set_signal(timer_signal);
	// Set it's duration
	// Set repeat and other props

	timer_debug_log << "finished timer constructer" << std::endl;
}

void Timer::update(double delta)
{
	if (proceed)
	{
		timer_debug_log << "checkiing... " << time_elapsed.count() << std::endl;
		time_elapsed += std::chrono::duration<double>(delta);
		if (time_elapsed >= duration)
		{
			finish_emitter.emit();
			timer_debug_log << "emitted timer finish signal" << std::endl;
			start_time = std::chrono::system_clock::now();
			time_elapsed = std::chrono::seconds(0);
			if (!repeat) proceed = false;
		}
	}
}
