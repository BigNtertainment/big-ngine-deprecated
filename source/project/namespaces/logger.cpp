#include <iostream>
#include <fstream>
#include "logger.h"

void Logger::Log(std::string message)
{
	std::printf(message.c_str());
}