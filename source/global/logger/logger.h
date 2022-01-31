#include <iostream>
#include <iostream>
#include <string>
#include <ctime>
#include "../../types/vector2/vector2.h"

namespace Logger
{
	void Log(const std::string& message);
	void Warn(const std::string& message);
	void Error(const std::string& message);


	void Log(float input);
	void Warn(float input);
	void Error(float input);


	void Log(double input);
	void Warn(double input);
	void Error(double input);


	void Log(int input);
	void Warn(int input);
	void Error(int input);

	void Log(const BigNgine::Vector2& input);
	void Warn(const BigNgine::Vector2& input);
	void Error(const BigNgine::Vector2& input);
}

std::string currentDateTime();