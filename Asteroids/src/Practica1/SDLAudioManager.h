#ifndef __SDL_AUDIO_MANAGER_H__
#define __SDL_AUDIO_MANAGER_H__

#include <map>
#include <SDL_mixer.h>

#include "AudioManager.h"

class SDLAudioManager : public AudioManager 
{
private:
	bool initialized_;
	int channels_;

	std::map<int, Mix_Chunk*> chunks_;
	std::map<int, Mix_Music*> music_;

public:
	SDLAudioManager();
	SDLAudioManager(int channels);
	virtual ~SDLAudioManager();

	virtual bool init();

	// Sound Effects
	virtual bool loadSound(int tag, std::string fileName);
	virtual int playChannel(int tag, int loops, int channel);
	virtual void pauseChannel(int channel);
	virtual void resumeChannel(int channel);
	virtual void haltChannel(int channel);
	virtual int setChannelVolume(int volume, int channel);
	virtual int channels();

	// Music
	virtual bool loadMusic(int tag, std::string fileName);
	virtual void playMusic(int tag, int loops);
	virtual int setMusicVolume(int volume);
	virtual void haltMusic();
	virtual void pauseMusic();
	virtual void resumeMusic();
};

#endif // !__SDL_AUDIO_MANAGER_H__