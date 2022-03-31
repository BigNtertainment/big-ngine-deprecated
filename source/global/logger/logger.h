#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include "../fileSystem/fileSystem.h"
#include "../../types/vector2/vector2.h"

#define CONSOLE_DEFAULT FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define CONSOLE_GREEN FOREGROUND_GREEN
#define CONSOLE_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define CONSOLE_RED FOREGROUND_RED

namespace Logger
{
	void SetConsoleColor(int color);
	std::string CurrentDateTime();

	template<typename T>
	void Log(const T &message, std::ostream &stream = std::cout)
	{
		// Change the console color
		SetConsoleColor(CONSOLE_DEFAULT);
		
		// Get the current date and time
		std::string currentDateTime = CurrentDateTime();
		
		// Write the message to the stream
		stream << "[" << currentDateTime << "][LOG] " << message << std::endl;
	}
	
	template<typename T>
	void Warn(const T &message, std::ostream &stream = std::cout)
	{
		// Change the console color
		SetConsoleColor(CONSOLE_YELLOW);
		
		// Get the current date and time
		std::string currentDateTime = CurrentDateTime();
		
		// Write the message to the stream
		stream << "[" << currentDateTime << "][WARN] " << message << std::endl;
		
		// Reset the console color
		SetConsoleColor(CONSOLE_DEFAULT);
	}
	
	template<typename T>
	void Error(const T &message, std::ostream &stream = std::cout)
	{
		// Change the console color
		SetConsoleColor(CONSOLE_RED);
		
		// Get the current date and time
		std::string currentDateTime = CurrentDateTime();
		
		// Write the message to the stream
		stream << "[" << currentDateTime << "][ERROR] " << message << std::endl;
		
		// Reset the console color
		SetConsoleColor(CONSOLE_DEFAULT);
	}
	
	template<typename T>
	void Success(const T &message, std::ostream &stream = std::cout)
	{
		// Change the console color
		SetConsoleColor(CONSOLE_GREEN);
		
		// Get the current date and time
		std::string currentDateTime = CurrentDateTime();
		
		// Write the message to the stream
		stream << "[" << currentDateTime << "][SUCCESS] " << message << std::endl;
		
		// Reset the console color
		SetConsoleColor(CONSOLE_DEFAULT);
	}		
}