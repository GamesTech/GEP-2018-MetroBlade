#pragma once
#include "FileManager.h"
#include <vector>
#include <windef.h>
#include <iostream>
class SpriteFileManager : public FileManager
{
public:
	void LoadFile(std::string file_name, std::vector<RECT> test_vec, std::string anim_type);
	void SaveFile(std::string file_name) override;
private:
	std::fstream anim_file;
};