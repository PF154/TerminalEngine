#pragma once

#include <ncurses.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>

// Would be cool if this was eventually user-configurable
enum InputType
{
	NONE,
	LEFT,
	RIGHT,
	QUIT
};

namespace Input
{
	// Using vector here instead of set to preserve order
	extern std::vector<InputType> input_buffer;

	void initialize_input();
	inline void end_input() { endwin(); };


	void get();

	void update();
	
	std::unordered_set<InputType> get_input_buffer();

	bool is_pressed(InputType input);

}