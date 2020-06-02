#ifndef __AUDIO_SYSTEM_H__
#define __AUDIO_SYSTEM_H__

#include "System.h"

class AudioSystem : public System
{
public:
	AudioSystem();

	void init() override;
	void update() override;
	void receive(const msg::Message& msg) override;
};

#endif // !__FOOD_SYSTEM_H__