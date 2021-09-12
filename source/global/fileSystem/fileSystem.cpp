#include "fileSystem.h"
#include "../logger/logger.h"

std::string FileSystem::LoadFile(const std::string& path)
{
	std::string result, temp;
	std::fstream file;
	file.open(path, std::ios::in);
	if (!file.good())
	{
		Logger::Error("Could not open file: " + path);
		return "";
	}
	while (file)
	{
		temp = "";
		getline(file, temp);
		if (file)
		{
			result += temp + "\n";
		}
	}

	file.close();
	return result;
}



void FileSystem::SaveFile(const std::string& path, const std::string& contents)
{
	std::fstream file;

	file.open(path, std::ios::trunc | std::ios::out);
	if (!file.good())
	{
		Logger::Error("Could not open or create file: " + path);
		return;
	}


	file << contents;
	file.close();
}


void FileSystem::AppendFile(const std::string& path, const std::string& contents)
{
	std::fstream file;
	std::fstream ifile;

	ifile.open(path);
	if (!ifile)
	{
		Logger::Error("Could not open file: " + path);
		return;
	}
	ifile.close();
	file.open(path, std::ios::app);
	if (!file.good())
	{
		Logger::Error("Could not open file: " + path);
		file.close();
		return;
	}

	file << contents;
	file.close();
}
