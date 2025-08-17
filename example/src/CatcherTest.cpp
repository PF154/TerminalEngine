#include "../include/CatcherTest.hpp"

#include <fstream>

std::ofstream catcher_debug_log("debug_log.txt", std::ios::app);

CatcherTest::CatcherTest ()
{

}

void CatcherTest::setup()
{
	create_signal_catcher(std::string("TEST_SIGNAL"), [this]() { send_debug_message(); });
}

void CatcherTest::send_debug_message()
{
	catcher_debug_log << "This is the message to indicate a recieved signal!" << std::endl;
}