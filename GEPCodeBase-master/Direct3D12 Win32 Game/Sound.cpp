#include "pch.h"
#include "Sound.h"

//TODO:: add reference to web-tutorials about adding Wave-banks


Sound::Sound(AudioEngine* _audEngine, string _filename)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	string fullpath = "../sounds/" + _filename + ".wav";
	std::wstring wFilename = converter.from_bytes(fullpath.c_str());

	m_sfx = std::make_unique<SoundEffect>(_audEngine, wFilename.c_str());

}


Sound::~Sound()
{
	m_sfx.reset();
}

void Sound::Play()
{
	if (m_sfx)
	{
		m_sfx->Play(m_volume, m_pitch, m_pan);
	}
}
