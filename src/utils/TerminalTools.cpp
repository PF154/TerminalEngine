#include <utils/TerminalTools.hpp>
#include <ncurses.h>

#include <iostream>

void moveCursorUp(int n) {
    // std::cout << "\033[" << n << "A";

    int current_y, current_x;
    getyx(stdscr, current_y, current_x);
    move(current_y - n, current_x);
}

void clearLine() {
    // std::cout << "\r\033[K";

    int current_y, current_x;
    getyx(stdscr, current_y, current_x);
    move(current_y, 0);
    clrtoeol();
}