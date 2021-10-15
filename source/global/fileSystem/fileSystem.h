#include <string>
#include <fstream>
#include <streambuf>
#include "../logger/logger.h"

namespace FileSystem
{
/// Reads text file to string
///	@param path Path to file
	std::string LoadFile(const std::string& path);

///	Saves contents to file
///	@param path Path to file
/// @param contents contents of file
///	@details It overrides any previous contents of file
	void SaveFile(const std::string& path, const std::string& contents);

///	Appends contents to file
///	@param path Path to file
/// @param contents contents of file
///	@details It puts contents to end of the file
	void AppendFile(const std::string& path, const std::string& contents);
}