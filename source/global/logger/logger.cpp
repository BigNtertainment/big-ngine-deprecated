#include "logger.h"

std::string Logger::CurrentDateTime() {
    time_t     now = time(nullptr);
    struct tm  tstruct{};
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Logger::SetConsoleColor(int color) {
	SetConsoleTextAttribute(hConsole, color);
}