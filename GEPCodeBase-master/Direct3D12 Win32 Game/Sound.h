#pragma once

#include "GameComponent.h"

#include "Audio.h"
#include <string>
#include <codecvt>
struct GameStateData;

//GEP:: Essential sound effect stuff here
// https://github.com/Microsoft/DirectXTK/wiki/Adding-the-DirectX-Tool-Kit-for-Audio
// More involved 3D sound system seems to be in place but the wiki documentation runs out

class AudioManager;

class SoundComponent :
	public GameComponent
{
public:
	SoundComponent(std::string filename);
	virtual ~SoundComponent();

	void initAudio();

	std::string  getSoundName() const;
	void setSoundFile(std::string new_sound);

	virtual void Play();
	virtual void Stop();

	void registerAudioManager(AudioManager* audio_system);
	AudioManager*  getAudioManager();

	virtual void tickComponent(GameStateData*  _GSD) override;
	virtual void renderComponent(RenderData*     _RD) override;

	// Component Utilities. 
	void SetVolume(float _vol) { m_volume = _vol; }
	float GetVolume() { return m_volume; }

	void SetPitch(float _pitch) { m_pitch = _pitch; }
	float GetPitch() { return m_pitch; }

	void SetPan(float _pan) { m_pan = _pan; }
	float GetPan() { return m_pan; }

	void isLooped(bool looped);

protected:
	std::string								  sound_name;
	AudioManager*								   audio;

	std::unique_ptr<DirectX::SoundEffectInstance>  sound; 

	float m_volume = 1.0f;
	float m_pitch = 0.0f;
	float m_pan = 0.0f;

	bool loop = false;
};

