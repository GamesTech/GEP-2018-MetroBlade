#pragma once
#include <fstream>
#include <string>
class FileManager
{
public:
	FileManager() = default;
	~FileManager() = default;

	virtual void LoadFile(std::string file_name);
	virtual void SaveFile(std::string file_name);
private:

	std::fstream new_file;
	
};