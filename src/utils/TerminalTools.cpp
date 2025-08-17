#include <utils/TerminalTools.hpp>

#include <iostream>

void moveCursorUp(int n) {
    std::cout << "\033[" << n << "A";
}

void clearLine() {
    std::cout << "\r\033[K";
}