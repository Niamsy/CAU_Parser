#pragma once

#include <fstream>
#include <string>

class FileManager
{
	std::fstream _file;
	std::string _fileName;

public:
	FileManager() = default;
	~FileManager();

	void Open(std::string const &, bool = false);
	void Close();
	void Write(std::string const &);
	void Remove();
	std::string Read();
};
