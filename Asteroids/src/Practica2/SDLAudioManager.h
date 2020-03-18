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

	virtual bool init() override;

	// Sound Effects
	virtual bool loadSound(int tag, std::string fileName) override;
	virtual int playChannel(int tag, int loops, int channel) override;
	virtual void pauseChannel(int channel) override;
	virtual void resumeChannel(int channel) override;
	virtual void haltChannel(int channel) override;
	virtual int setChannelVolume(int volume, int channel) override;
	virtual int channels() override;

	// Music
	virtual bool loadMusic(int tag, std::string fileName) override;
	virtual void playMusic(int tag, int loops) override;
	virtual int setMusicVolume(int volume) override;
	virtual void haltMusic() override;
	virtual void pauseMusic() override;
	virtual void resumeMusic() override;
};

#endif // !__SDL_AUDIO_MANAGER_H__