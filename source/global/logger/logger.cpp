#include <iostream>
#include <time.h>
#include "logger.h"

#define NC "\e[0m%-6s\e[m"
#define WARNING "\e[93;10m%-6s\e[m"
#define ERROR "\e[91;1m%-6s\e[m"

void Logger::Log(std::string message)
{
	message = "[" + currentDateTime() + "][INFO] " + message + "\n";

	std::printf( NC, message.c_str());
}

void Logger::Warn(std::string message)
{
	message = "[" + currentDateTime() + "][WARNING] " + message + "\n";

	std::printf( WARNING, message.c_str());
}

void Logger::Error(std::string message)
{
	message = "[" + currentDateTime() + "][ERROR] " + message + "\n";

	std::printf( ERROR, message.c_str());
}


const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}