/**
*  @file    AudioManager.h
*  @author  Nathan Butt (GitHub - n86-64)
*  @date    07/05/2018
*  @version v1.0
*
*  @section System Module
*           Audio.
*
*  @brief Definition for Audio Manager System. 
*
*  @section Description
*
*  The subsystem component risponcable for paudio loading and playback.
*  SoundComponents use this in order to playback sounds. 
*/

#pragma once


#include "pch.h"


struct SoundData 
{
	SoundData() {};
	SoundData(SoundData&&) = default;
	std::string   sound_name = "NULLSOUND";
	std::unique_ptr<DirectX::SoundEffect>   sound_data = nullptr;
};


class AudioManager 
{
public:
	AudioManager();
	~AudioManager();

	void registerSoundComponents(std::vector<SoundComponent*> sound_components); // Register any sound components in the object.

	DirectX::SoundEffectInstance* loadSound(std::string sound_name);

	// Audio Manager Configuration.
	void setVolume(float new_vol);
	float getVolume() const;


	// Scene manager functions. 
	void updateAudioManager(); 
	void pauseAudioEngine();
	void resumeAudioEngine();

	void clear();

private:
	int findSoundData(std::string  filename);
	void loadAudioFromDisk(std::string filename);

private: 
	std::vector<SoundData>				  system_sounds;
	std::vector<SoundComponent*>	   audio_components;

	std::unique_ptr<DirectX::AudioEngine>  sound_engine;

	float								  volume = 1.0f;
};