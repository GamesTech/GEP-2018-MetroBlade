/**
*  @file    FileReaderBase.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    14/03/2018
*  @version v1.0
*
*  @section System Module
*           Core State Manager.
*
*  @brief Definition for FileReader Template.
*
*  @section Description
*
*  FileReader template is a base structure definition that all file readers will use.
*/


#pragma once

#include "pch.h"
#include <fstream>


class FileReaderBase 
{
public:
	FileReaderBase() = delete; 
	virtual ~FileReaderBase() = default;

	bool readFile(std::string  file_path);

private:
	// storage for file data.
	std::string			  file_buffer; 
};