#include "fileSystem.h"

std::string FileSystem::LoadFile(const std::string& path)
{
	std::ifstream file(path);
	std::string result;

	file.seekg(0, std::ios::end);   
	result.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	result.assign((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());

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
