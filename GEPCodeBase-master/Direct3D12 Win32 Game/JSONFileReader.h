/**
*  @file    JSONFileReader.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    14/03/2018
*  @version v1.0
*
*  @section System Module
*           File IO Management
*
*  @brief Definition for JSONFileReader Template.
*
*  @section Description
*
*  JSONFileReader is a defined component that is used for reading data from JSON style documents.
*
*  @section Citation
*		
*	Originally used as part of another project in Low Level Programming module (April 2018)
*/

#pragma once

#include "pch.h"
#include <jsoncons\json.hpp>

class JSONFileReader 
{
public:
	JSONFileReader() = default;

	void			setFilePath(std::string new_file_path);
	bool			parseFile();
	jsoncons::json&	getFileBuffer();

private:
	std::string			file_path = "NULL";
	jsoncons::json		file_buffer;
};