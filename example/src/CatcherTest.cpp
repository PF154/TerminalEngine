#include "../include/CatcherTest.hpp"

#include <fstream>

std::ofstream catcher_debug_log("debug_log.txt", std::ios::app);

CatcherTest::CatcherTest ()
{
	catcher_debug_log << "Catcher constructor initiated" << std::endl;

	catcher_debug_log << "Catcher constructor completed" << std::endl;
}

void CatcherTest::init()
{
	// Create the catcher here
	create_signal_catcher(std::string("TEST_SIGNAL"), [this]() { send_debug_message(); });
}

void CatcherTest::send_debug_message()
{
	catcher_debug_log << "This is the message to indicate a recieved signal!" << std::endl;
}