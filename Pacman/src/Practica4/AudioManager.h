#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include <string>

class AudioManager
{
public:
	AudioManager();
	virtual ~AudioManager();

	virtual bool init() = 0;

	// Sound Effects
	virtual bool loadSound(int tag, std::string fileName) = 0;
	virtual int playChannel(int tag, int loops, int channel = -1) = 0;
	virtual void pauseChannel(int channel = -1) = 0;
	virtual void resumeChannel(int channel = -1) = 0;
	virtual void haltChannel(int channel = -1) = 0;
	virtual int setChannelVolume(int volume, int channel = -1) = 0;
	virtual int channels() = 0;

	// Music
	virtual bool loadMusic(int tag, std::string fileName) = 0;
	virtual void playMusic(int tag, int loops = -1) = 0;
	virtual int setMusicVolume(int volume) = 0;
	virtual void haltMusic() = 0;
	virtual void pauseMusic() = 0;
	virtual void resumeMusic() = 0;
};

#endif // !__AUDIO_MANAGER_H__