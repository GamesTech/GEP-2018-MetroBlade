#include "pch.h"

#include "AudioManager.h"
#include "Sound.h"
//TODO:: add reference to web-tutorials about adding Wave-banks


SoundComponent::SoundComponent(AudioEngine* _audEngine, string _filename)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	string fullpath = "../sounds/" + _filename + ".wav";
	std::wstring wFilename = converter.from_bytes(fullpath.c_str());

	m_sfx = std::make_unique<SoundEffect>(_audEngine, wFilename.c_str());
}


SoundComponent::~SoundComponent()
{
	m_sfx.reset();
}

void SoundComponent::setSoundFile(std::string new_sound)
{
	sound_name = new_sound;
	sound.reset(audio->loadSound(new_sound));
}

void SoundComponent::Play()
{
	if (m_sfx)
	{
		m_sfx->Play(m_volume, m_pitch, m_pan);
	}
}

void SoundComponent::Stop()
{
	// Here the sound can be stopped.
}

void SoundComponent::registerAudioManager(AudioManager * audio_system)
{
	audio = audio_system;
}

void SoundComponent::tickComponent(GameStateData * _GSD)
{
	return;
}

void SoundComponent::renderComponent(RenderData * _RD)
{
	return;
}

