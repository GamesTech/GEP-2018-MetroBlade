#include "SpriteFileManager.h"

void SpriteFileManager::LoadFile(std::string file_name, std::vector<RECT> test_vec)
{
	anim_file.open(file_name, std::ios_base::in);

	if (anim_file.is_open())
	{
		while (!anim_file.eof())
		{
			for (int anim_num = 0; anim_num < test_vec.size(); anim_num++)
			{
				anim_file >> test_vec[anim_num].left;
				anim_file >> test_vec[anim_num].top;
				anim_file >> test_vec[anim_num].right;
				anim_file >> test_vec[anim_num].bottom;
				std::cout << test_vec[anim_num].left << test_vec[anim_num].top << test_vec[anim_num].right << test_vec[anim_num].bottom;
			}
		}
		anim_file.close();
	}
	else
	{
		//file failed to open so crash the entire system
	}
}

void SpriteFileManager::SaveFile(std::string file_name)
{

}