#include "pch.h"
#include "SpriteAnimFileReader.h"

SpriteAnimFileReader::SpriteAnimFileReader()
{
}

SpriteAnimFileReader::SpriteAnimFileReader(std::string file_location)
	: file_name(file_location)
{}

void SpriteAnimFileReader::setFileName(std::string file_location)
{
	file_name = file_location;
}

bool SpriteAnimFileReader::parseFile(std::vector<AnimationData>& anim_data_buffer)
{
	bool    error = readFile(file_name);

	if (!error)
	{
		anim_data_buffer.reserve(10);
		AnimationData  temp_data;
		std::string    temp;

		for (int i = 0; i < file_buffer.length(); i++) 
		{
			if (file_buffer[i] == '\n') 
			{
				// TODO - consider mobing to a seperate function.
				if ((97 <= (int)temp[0]) && ((int)temp[0] <= 122)) 
				{
					if (temp_data.anim_state_name != "null_state") 
					{
						anim_data_buffer.push_back(temp_data);
						temp_data = AnimationData();
					}
					getAnimStateName(temp_data, temp);
				}
				else if ((48 <= temp[0]) && (temp[0] <= 57)) 
				{
					getAnimFrameData(temp_data, temp);
				}
				else if (temp[0] == 62) 
				{
					
					temp_data.time_step = (1 / (float)std::atof(temp.c_str()));
				}
				else 
				{
					error = true;
				}
				temp = "";
			}
			else 
			{
				temp += file_buffer[i];
			}

			if (error) 
			{
				break;
			}
		}
	}

	return error;
}

void SpriteAnimFileReader::getAnimStateName(AnimationData& anim_buffer, std::string& temp)
{
	std::string   name;
	for (auto& string_char : temp) 
	{
		if (string_char == ':') 
		{
			break;
		}
		name += string_char;
	}
	anim_buffer.anim_state_name = name;
}

void SpriteAnimFileReader::getAnimFrameData(AnimationData& anim_buffer, std::string & temp)
{
	float rect_bounds[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	int i = 0;
	std::string  rect_value;

	for (auto& string_char : temp) 
	{
		if (string_char == ' ') 
		{
			rect_bounds[i] = (float)std::stof(rect_value);
			rect_value = "";
			i++;
		}
		else 
		{
			rect_value += string_char;
		}

		if (i == 4) 
		{
			break;
		}
	}

	RECT   new_rect;
	new_rect.top    = rect_bounds[0];
	new_rect.left   = rect_bounds[1];
	new_rect.bottom = rect_bounds[2];
	new_rect.right  = rect_bounds[3];
	anim_buffer.anim_frames.push_back(new_rect);
}
