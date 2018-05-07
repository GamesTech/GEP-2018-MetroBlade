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
	std::string   sound_name = "NULLSOUND";
	std::unique_ptr<DirectX::SoundEffect>   sound_data;
};


class AudioManager 
{
public:
	AudioManager();
	~AudioManager();

	void registerSoundComponents(std::vector<SoundComponent*> sound_components); // Register any sound components in the object.


	// Scene manager functions. 
	void updateAudioManager(); 
	void pauseAudioEngine();
	void resumeAudioEngine();

private: 
	std::vector<SoundData>				  system_sounds;
	std::vector<SoundComponent*>	   audio_components;

	std::unique_ptr<DirectX::AudioEngine>  sound_engine;
};