#include "pch.h"
#include "FileReaderBase.h"

bool FileReaderBase::readFile(std::string file_path)
{
	bool			error = false;
	std::fstream    file;
	file.open(file_path, std::fstream::in);

	error = file.fail();

	if (!error) 
	{
		while (!file.eof()) 
		{
			file_buffer += (char)file.get();
		}
	}

	file.close();
	return error;
}