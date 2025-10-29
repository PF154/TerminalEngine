#pragma once

#include <chrono>
#include <string>
#include <core/EventSystem/SignalEmitter.hpp>
#include <core/EventSystem/EventHandler.hpp>

class Timer
{
	public:
		Timer () {};
		Timer (std::string socket_id, std::shared_ptr<EventHandler> event_handler);

		// We need to figure out what to do if the user does not set duration
		// Maybe just have a default duration?

		void update(double delta);

		inline std::string get_socket_id() { return m_socket_id; }

		bool repeat = false;

		void set_duration(std::chrono::duration<double> new_dur) { duration = new_dur; }

	private:
		std::chrono::time_point<std::chrono::system_clock> start_time;
		std::chrono::duration<double> time_elapsed;

		std::string m_socket_id;

		std::chrono::duration<double> duration = std::chrono::seconds(1);
		bool proceed = true;

		SignalEmitter finish_emitter;
};