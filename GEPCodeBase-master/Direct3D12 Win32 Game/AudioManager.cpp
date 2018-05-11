#include "pch.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{
	system_sounds.reserve(100);
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
		component->initAudio();
		component->SetVolume(volume);
		audio_components.push_back(component);
	}
}

DirectX::SoundEffectInstance* AudioManager::loadSound(std::string sound_name)
{
	int sound_data_index = findSoundData(sound_name);

	if (sound_data_index == -1) 
	{
		// Here we load the sound from the file if it dosent exist.
		loadAudioFromDisk(sound_name);
		sound_data_index = system_sounds.size() - 1;
	}
	
	return (system_sounds[sound_data_index].sound_data->CreateInstance().release());
}

void AudioManager::setVolume(float new_vol)
{
	volume = new_vol;
	for (auto& components : audio_components) 
	{
		components->SetVolume(volume);
	}
}

float AudioManager::getVolume() const
{
	return volume;
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

void AudioManager::clear()
{
	// Stop all sounds playing and then clear the audio buffer. 
	for (auto& component : audio_components) 
	{
		component->Stop();
	}

	audio_components.clear();
}

int AudioManager::findSoundData(std::string filename)
{
	int index = -1;
	for (int i = 0; i < system_sounds.size(); i++) 
	{
		if (filename == system_sounds[i].sound_name) 
		{
			index = i;
			break;
		}
	}

	return index;
}

void AudioManager::loadAudioFromDisk(std::string filename)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	string fullpath = "../sounds/" + filename + ".wav";
	std::wstring wFilename = converter.from_bytes(fullpath.c_str());

	SoundData  new_data;
	new_data.sound_name = filename;
	new_data.sound_data = std::make_unique<DirectX::SoundEffect>(sound_engine.get(), wFilename.c_str());
	system_sounds.push_back(std::move(new_data));
}