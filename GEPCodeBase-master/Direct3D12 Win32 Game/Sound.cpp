#include "pch.h"

#include "AudioManager.h"
#include "Sound.h"
//TODO:: add reference to web-tutorials about adding Wave-banks


SoundComponent::SoundComponent(std::string filename)
	:sound_name(filename)
{
}

SoundComponent::~SoundComponent()
{
	m_sfx.reset();
}

void SoundComponent::initAudio()
{
	if (sound_name != "") 
	{
		setSoundFile(sound_name);
	}
}

void SoundComponent::setSoundFile(std::string new_sound)
{
	sound_name = new_sound;
	sound.reset(audio->loadSound(new_sound));
}

void SoundComponent::Play()
{
	if (sound) 
	{
		if (sound->GetState() == PLAYING) 
		{
			sound->Stop();
		}

		sound->Play(loop);
	}
}

void SoundComponent::Stop()
{
	// Here the sound can be stopped.
	sound->Stop();
}

void SoundComponent::registerAudioManager(AudioManager* audio_system)
{
	audio = audio_system;
}

AudioManager* SoundComponent::getAudioManager()
{
	return audio;
}

void SoundComponent::tickComponent(GameStateData * _GSD)
{
	
	return;
}

void SoundComponent::renderComponent(RenderData * _RD)
{
	return;
}

void SoundComponent::isLooped(bool looped)
{
	loop = looped;
}

