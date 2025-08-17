#pragma once

#include <core/EventSystem/Signal.hpp>
#include <core/EventSystem/EventHandler.hpp>
#include <core/SceneData.hpp>

#include <memory>
#include <string>
#include <functional>
#include <iostream>

/* Essentially we want some logic to do the following: We want a function that will be called by GameObject's update
	function automatically. The user should not have to set this up. GameObject should have a list of recievers
	and part of the update loop should be to automatically call attempt_catch on every one of them.
	Every Catcher needs a function pointer to a function in it's respective game object. This function will
	automatically be called upon catch. This is essentially how godot does it. 
	
	The hard part is figuring out how we want to get the ID into the Catcher. Can we some how connect it to
	the emitter directly? If we can, then what is the point of the EventHandler? At the moment, I can't think
	of a way to actually connect the emitters to the recievers directly, because this would maybe cause some issues
	with multiple emitters/recievers for the same signal/socket. Maybe I'll think of a way to do that later, but
	I think maybe the better option is for EventHandler to have a map of socket names which are defined by the
	user. Therefore the user (Or TimerManager type object) will define a name such as "PLAYER_AREA_ENTERED" and give
	this name to both the emitter and the reciever. The first to be set up will set up the socket, and the second
	will just link into it. We probably want some sort of check to make sure that things are aligned properly. For
	instance, we could set up a "reference count" and warn the developer at the start of runtime that a particular
	socket is lacking at least one emitter or reciever. It'd also be cool if we could do some sort of fuzzy
	string matching to do typo detection.*/

// struct SignalCatcherBase {
//     virtual ~SignalCatcherBase() = default;
//     virtual void attempt_catch() = 0;
// };


// 1: Decide what information the Signal Catcher needs
// 2: Remove unnecessary information
// 3: Create a constructor that takes in the needed info or sets it from context
// 4: Rewrite the factory in GameObject to use the new constructor

// template <typename T>
class SignalCatcher
{
	// using OwnerFunc = void(T::*)(std::shared_ptr<Signal>);

	public:
		SignalCatcher() {};
		// SignalCatcher(std::unique_ptr<T> owner, std::shared_ptr<EventHandler> event_handler, std::string socket_name, OwnerFunc catch_function)
		// 	: m_owner(owner), m_event_handler(event_handler), m_catch_func(catch_function){};
		SignalCatcher(std::shared_ptr<EventHandler> event_handler, std::string socket_name, std::function<void()> catch_function)
			: m_event_handler(event_handler), m_event_socket_name(socket_name), m_catch_function(catch_function) {};


		void set_socket(std::string socket)
		{
			m_event_socket_name = socket;
		}

		void attempt_catch();

	private:

		std::shared_ptr<EventHandler> m_event_handler;
		std::string m_event_socket_name;

		/* This makes me think that we need some kind of standard thing to be passed into the function pointer
		Maybe just a pointer to the signal, and let the catch function decide how to parse it? Maybe this is
		a good candidate for a template? Idk.*/
		// OwnerFunc m_catch_func;
		// std::function<void(std::shared_ptr<Signal>)> catch_function;
		std::function<void()> m_catch_function;

};