#include "FileManager.h"

void FileManager::LoadFile(std::string file_name)
{
	new_file.open(file_name);

	if (new_file.is_open())
	{
		//do something with the stuff in the file
		new_file.close();
	}
	else
	{
		//file failed to open so crash the entire system
	}

	
}

void FileManager::SaveFile(std::string file_name)
{
	new_file.open(file_name);

	if (new_file.is_open())
	{
		//do something with the stuff in the file
		new_file.close();
	}
	else
	{
		//file failed to open so crash the entire system
	}
}