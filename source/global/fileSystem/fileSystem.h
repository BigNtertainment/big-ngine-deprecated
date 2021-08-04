namespace FileSystem
{
	std::string LoadFile(std::string path);

	void SaveFile(std::string path, std::string contents);

	void AppendFile(std::string path, std::string contents);
}