#pragma once

#include <ncurses.h>

// Would be cool if this was eventually user-configurable
enum InputType
{
	NONE,
	LEFT,
	RIGHT
};

namespace Input
{
	void initialize_input()
	{
		initscr();

		cbreak();
		noecho();	

		nodelay(stdscr, TRUE);
	}


	InputType get_input()
	{
		int ch;

		ch = getch();
		if (ch == 'a') return InputType::LEFT;
		else if (ch == 'd') return InputType::RIGHT;
		else return InputType::NONE;
	}
	

	void end_input()
	{
		endwin();
	}

}