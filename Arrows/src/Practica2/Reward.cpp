#include "Reward.h"


Reward::Reward(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	ArrowsGameObject(g, t, w, h, p, d, s, a),
	EventHandler(),
	state_ (RewardState::BUBBLED)
{
}

Reward::~Reward()
{
}

void Reward::update()
{
}

void Reward::render() const
{
}

void Reward::handleEvents(SDL_Event& event)
{
}