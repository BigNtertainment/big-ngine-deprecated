#include <iostream>

namespace Logger
{
	void Log(std::string message);
	void Warn(std::string message);
	void Error(std::string message);


	void Log(float input);
	void Warn(float input);
	void Error(float input);


	void Log(double input);
	void Warn(double input);
	void Error(double input);


	void Log(int input);
	void Warn(int input);
	void Error(int input);
}

const std::string currentDateTime();