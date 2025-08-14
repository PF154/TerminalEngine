#pragma once

#include "Signal.hpp"

#include <unordered_map>
#include <memory>
#include <string>

/* So this is the event handler. Essentially, both the scene and anything that relies on events will have
   access to the same event handler. Let's say the event in question is a timer. There will be three objects
   that talk to this event. (I think actually the timers will need thier own TimerManager class that can be
   called update() on, but we can handle that later). So we have the timer. Every time TimerManager.update()
   is called, the timers are incremented. If the timer has gone off, it sends a signal to the EventHandler
   class. I think the signal should be a specific class itself, so that we can carry different kinds of data
   with it. The signal is put into some "socket" in the EventHandler. This socket is being checked on update
   by the GameObject that depends on it. Once the socket is populated, the GameObject "recieves" the signal
   and does whatever it needs to upon that signal's arrival.*/

class EventHandler
{
	private:
	   std::unordered_map<std::string, std::shared_ptr<Signal>> signal_map;
      int next_unique_id = 0;

   public:
      std::string generate_unique_name();

      std::shared_ptr<Signal> retrieve_socket(std::string socket_id);

      void populate_socket(std::string socket_id, std::shared_ptr<Signal> signal);

      void verify_socket(std::string socket_name)
      {
         if (signal_map.count(socket_name) == 0) signal_map[socket_name] = nullptr;
      }
};