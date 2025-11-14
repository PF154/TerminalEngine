#include <input/Input.hpp>

#include <vector>
#include <unordered_set>

std::vector<InputType> Input::input_buffer;

void Input::initialize_input()
{
	input_buffer.push_back(InputType::NONE);

	initscr();

	cbreak();
	noecho();	

	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
}

void Input::get()
{
	// Eventually could figure out difference between press/hold/release here?

	int ch;

	ch = getch();
	if (ch == 'a') input_buffer.push_back(InputType::LEFT);
	else if (ch == 'd') input_buffer.push_back(InputType::RIGHT);
	else if (ch == 'q') input_buffer.push_back(InputType::QUIT);
}

void Input::update()
{
	// Clear buffer
	input_buffer.clear();
	input_buffer.push_back(InputType::NONE);
}

// not sure if this function will ever actually be useful
// felt cute, will probably delete later
std::unordered_set<InputType> Input::get_input_buffer()
{
	std::unordered_set<InputType> ret;
	// Resolve input
	// currently, no difference between press/hold/release. A button is either down during a frame or it isn't
	for (InputType in : input_buffer)
	{
		if (!ret.contains(in)) ret.emplace(in);
	}

	return ret;
}

bool Input::is_pressed(InputType input)
{
	if (get_input_buffer().contains(input)) return true;
	return false;
}