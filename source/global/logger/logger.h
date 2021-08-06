namespace Logger
{
	void Log(std::string message);
	void Warn(std::string message);
	void Error(std::string message);


	void Log(float input);
	void Warn(float input);
	void Error(float input);


	void Log(double input);
	void Warn(double message);
	void Error(double message);


	void Log(int input);
	void Warn(int message);
	void Error(int message);
}

const std::string currentDateTime();