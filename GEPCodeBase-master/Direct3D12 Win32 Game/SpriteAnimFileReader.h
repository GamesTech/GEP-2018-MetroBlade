/**
*  @file    SpriteAnimFileReader.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    14/03/2018
*  @version v1.0
*
*  @section System Module
*           Core State Manager.
*
*  @brief Definition for Sprite Anmation File Reader Data.
*
*  @section Description
*
*  A FileReader definition that allows animation data to be parsed. 
*/


#pragma once

#include "FileReaderBase.h"
#include "AnimationData.h"

class SpriteAnimFileReader : public FileReaderBase 
{
public:
	SpriteAnimFileReader();
	SpriteAnimFileReader(std::string   file_location);
	~SpriteAnimFileReader() = default;

	void setFileName(std::string   file_location);
	bool parseFile(std::vector<AnimationData>&  anim_data_buffer);

private:
	void  getAnimStateName(AnimationData&  anim_buffer, std::string& temp);
	void  getAnimFrameData(AnimationData&  anim_buffer, std::string& temp);
	std::string     file_name;
};