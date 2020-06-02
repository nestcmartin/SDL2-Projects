#ifndef __ANIMATED_IMAGE_H__
#define __ANIMATED_IMAGE_H__

#include <iostream>
#include <cassert>
#include <utility>
#include <vector>

#include "Component.h"

#include "Texture.h"

struct AnimatedImage : Component
{
	using Sprite = std::pair<Texture*, SDL_Rect>;

private:
	std::vector<Sprite> sprites_;

	Uint32 spriteTime_;
	Uint32 currentSprite_;
	Uint32 lastTimeChanged_;

public:
	AnimatedImage() :
		Component(ECS::AnimatedImageComponent),
		sprites_(),
		spriteTime_(0),
		currentSprite_(0),
		lastTimeChanged_(0)
	{
	}

	void setSpriteTime(Uint32 spriteTime) 
	{
		assert(spriteTime >= 0);
		spriteTime_ = spriteTime;
	}

	void addSprite(Texture* tex, SDL_Rect clip) 
	{
		sprites_.push_back({ tex, clip });
	}

	const Sprite& getSprite(Uint32 time) 
	{
		if (time > lastTimeChanged_ + spriteTime_) 
		{
			lastTimeChanged_ = time;
			currentSprite_ = (currentSprite_ + 1) % sprites_.size();
		}

		return sprites_[currentSprite_];
	}

	void reset()
	{
		sprites_.clear();
		spriteTime_ = 0;
	}
};

#endif // !__ANIMATED_IMAGE_H__