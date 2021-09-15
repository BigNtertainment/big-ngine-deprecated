#include <string>
#include <fstream>
#include <streambuf>
#include "../logger/logger.h"

namespace FileSystem
{
	std::string LoadFile(const std::string& path);

	void SaveFile(const std::string& path, const std::string& contents);

	void AppendFile(const std::string& path, const std::string& contents);
}