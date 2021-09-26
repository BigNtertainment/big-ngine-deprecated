#include <iostream>
#include <iostream>
#include <string>
#include <ctime>
#include "../../types/vector2/vector2.h"

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

	void Log(BigNgine::Vector2 input);
	void Warn(BigNgine::Vector2 input);
	void Error(BigNgine::Vector2 input);
}

const std::string currentDateTime();