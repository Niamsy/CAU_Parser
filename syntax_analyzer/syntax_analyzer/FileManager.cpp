#include "FileManager.h"
#include "pch.h"

FileManager::~FileManager()
{
	if (_file && _file.is_open())
		Close();
}

void FileManager::Open(std::string const &filePath, bool createFile)
{
	if (createFile) {
		std::ofstream ofs;
		ofs.open(filePath, std::ofstream::out | std::ofstream::trunc); // To delete file if exist
		ofs.close();
		_file.open(filePath, std::ofstream::out | std::ofstream::trunc); // Then to create it
		_file.close();
	}
	_file.open(filePath, std::ios::in | std::ios::app);
	_fileName = filePath;
	if (!_file) {
		throw std::exception("Error while opening file");
	}
}

void FileManager::Close()
{
	if (_file && _file.is_open()) {
		_file.close();
	}
}

void FileManager::Write(std::string const &toWrite)
{
	if (_file && _file.is_open())
		_file << toWrite;
	else {
		throw std::exception("Error while writing file");
	}
}

void FileManager::Remove()
{
	remove(_fileName.c_str());
}

std::string FileManager::Read()
{
	std::string		line;
	std::string		content;

	if (_file && _file.is_open())
	{
		while (!_file.eof() && std::getline(_file, line))
		{
			content += line;
			content += '\n';
		}
	}
	return content;
}

