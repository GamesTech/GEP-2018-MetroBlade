#include "pch.h"

#include "JSONFileReader.h"

void JSONFileReader::setFilePath(std::string new_file_path)
{
	file_path = new_file_path;
}

bool JSONFileReader::parseFile()
{
	std::ifstream file(file_path);
	bool file_valid = (!file.fail());

	if (file_valid) 
	{
		file >> file_buffer;
	}

	return file_valid;
}

jsoncons::json& JSONFileReader::getFileBuffer()
{
	return file_buffer;
}
