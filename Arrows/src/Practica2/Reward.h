#ifndef __REWARD_H__
#define __REWARD_H__

#include "ArrowsGameObject.h"
#include "EventHandler.h"

class Reward : public ArrowsGameObject, public EventHandler
{
	enum RewardState { BUBBLED, NOT_BUBBLED };

private:
	RewardState state_;

public:
	Reward(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
	virtual ~Reward();

	virtual void update();
	virtual void render() const;
	virtual void handleEvents(SDL_Event& event);
};

#endif // !__REWARD_H__