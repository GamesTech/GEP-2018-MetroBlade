#include "pch.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	sound_engine = std::make_unique<AudioEngine>(eflags);
}

AudioManager::~AudioManager()
{
	if (sound_engine) 
	{
		sound_engine->Suspend();
	}
}

void AudioManager::registerSoundComponents(std::vector<SoundComponent*> sound_components)
{
	for (auto& component : sound_components) 
	{
		// Here we register our sound components to assign them the audio manager as well as allowing files to be laoded and played.
		component->registerAudioManager(this);
		sound_components.push_back(component);
	}
}

void AudioManager::updateAudioManager()
{
	if (!sound_engine->Update())
	{
		if (sound_engine->IsCriticalError())
		{
			// We lost the audio device!
			// Here we should reset and print a message. 
		}
	}
	else 
	{
		// Update settings within components as well as any other issues.
	}
}

void AudioManager::pauseAudioEngine()
{
	sound_engine->Suspend();
}

void AudioManager::resumeAudioEngine()
{
	sound_engine->Resume();
}
