#pragma once

#include "AudioManager.h"
#include <SDL_mixer.h>

#include <map>

/*
 *
 */
class SDLAudioManager: public AudioManager {
public:
	SDLAudioManager();
	SDLAudioManager(int channels);
	virtual ~SDLAudioManager();

	// supposed to be called before start using the object
	virtual bool init();

	// sound effects
	virtual bool loadSound(int tag, string fileName);
	virtual int playChannel(int tag, int loops, int channel);
	virtual void pauseChannel(int channel);
	virtual void resumeChannel(int channel);
	virtual void haltChannel(int channel);
	virtual int setChannelVolume(int volume, int channel);
	virtual int channels();

	// music
	virtual bool loadMusic(int tag, string fileName);
	virtual void playMusic(int tag, int loops);
	virtual int setMusicVolume(int volume);
	virtual void haltMusic();
	virtual void pauseMusic();
	virtual void resumeMusic();

private:
	bool initialized_;
	int channels_;
	map<int, Mix_Chunk*> chunks_;
	map<int, Mix_Music*> music_;
};

