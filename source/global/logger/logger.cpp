#include "logger.h"

#include <windows.h>

//the logger coloring works only on Windows, also sets your terminal background to black no matter what color you had

// string
void Logger::Log(const std::string& message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << "[" << currentDateTime() << "][INFO] " << message << std::endl;
	
}

void Logger::Warn(const std::string& message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	
	std::cout << "[" << currentDateTime() << "][WARNING] " << message << std::endl;
	
}

void Logger::Error(const std::string& message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	
	std::cout << "[" << currentDateTime() << "][ERROR] " << message << std::endl;
	
}


void Logger::Log(float input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << "[" << currentDateTime() << "][INFO] " << std::to_string(input) << std::endl;
	
}

void Logger::Warn(float input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	
	std::cout << "[" << currentDateTime() << "][WARNING] " << std::to_string(input) << std::endl;
	
}

void Logger::Error(float input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	
	std::cout << "[" << currentDateTime() << "][ERROR] " << std::to_string(input) << std::endl;
	
}


// double
void Logger::Log(double input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << "[" << currentDateTime() << "][INFO] " << std::to_string(input) << std::endl;
	
}

void Logger::Warn(double input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	
	std::cout << "[" << currentDateTime() << "][WARNING] " << std::to_string(input) << std::endl;
	
}

void Logger::Error(double input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	
	std::cout << "[" << currentDateTime() << "][ERROR] " << std::to_string(input) << std::endl;
	
}


// int
void Logger::Log(int input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << "[" << currentDateTime() << "][INFO] " << std::to_string(input) << std::endl;
	
}

void Logger::Warn(int input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	
	std::cout << "[" << currentDateTime() << "][WARNING] " << std::to_string(input) << std::endl;
	
}

void Logger::Error(int input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	
	std::cout << "[" << currentDateTime() << "][ERROR] " << std::to_string(input) << std::endl;
	
}


//vector 2
void Logger::Log(const BigNgine::Vector2& input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << "[" << currentDateTime() << "][INFO] " << std::to_string(input.x) << " " << std::to_string(input.y) << std::endl;
	
}

void Logger::Warn(const BigNgine::Vector2& input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	
	std::cout << "[" << currentDateTime() << "][WARNING] " << std::to_string(input.x) << " " << std::to_string(input.y) << std::endl;
	
}

void Logger::Error(const BigNgine::Vector2& input)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	
	std::cout << "[" << currentDateTime() << "][ERROR] " << std::to_string(input.x) << " " << std::to_string(input.y) << std::endl;
	
}


std::string currentDateTime() {
    time_t     now = time(nullptr);
    struct tm  tstruct{};
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}