#include "Reward.h"
#include "GameState.h"
#include "PlayState.h"

Reward::Reward(GameState* g, Texture* t, Texture* bt, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	ArrowsGameObject(g, t, w, h, p, d, s, a),
	EventHandler(),
	bubbleTexture_(bt),
	bubbled_(true),
	used_(false),
	spriteColumn_(0)
{
	spriteRow_ = rand() % 2;
}

Reward::~Reward()
{
}

void Reward::update()
{
	if (!bubbled_) animate();
	else bubbled_ = !static_cast<PlayState*>(state_)->hitRewardBubble(this);
	ArrowsGameObject::update();

	if (position_.getY() > WIN_HEIGHT || used_)
	{
		static_cast<PlayState*>(state_)->killReward(iterator_, eventHandlerIt_);
	}
}

void Reward::render() const
{
	SDL_Rect destRect = getDestRect();
	texture_->renderFrame(destRect, spriteRow_, spriteColumn_, angle_);

	if (bubbled_)
	{
		destRect = getCollisionRect();
		bubbleTexture_->renderFrame(destRect, 0, 0, angle_);
	}
}

bool Reward::handleEvents(SDL_Event& event)
{
	if (bubbled_) return false;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p;
			SDL_GetMouseState(&p.x, &p.y);
			if (SDL_PointInRect(&p, &getDestRect()))
			{
				if (spriteRow_ == 0) static_cast<PlayState*>(state_)->rewardNextLevel();
				else if (spriteRow_ == 1) static_cast<PlayState*>(state_)->rewardMoreArrows();
				used_ = true;
				return true;
			}
		}
	}
	return false;
}

void Reward::saveToFile(std::ofstream& stream)
{
	ArrowsGameObject::saveToFile(stream);
	stream << spriteRow_ << " " << spriteColumn_ << " " << bubbled_ << " ";
}

void Reward::loadFromFile(std::ifstream& stream)
{
	ArrowsGameObject::loadFromFile(stream);
	stream >> spriteRow_ >> spriteColumn_ >> bubbled_;
}

SDL_Rect Reward::getCollisionRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(position_.getX() + (REWARD_WIDTH / 2) - (REWARD_BUBBLE_WIDTH / 2));
	rect.y = static_cast<int>(position_.getY() + (REWARD_HEIGHT / 2) - (REWARD_BUBBLE_HEIGHT / 2));
	rect.w = REWARD_BUBBLE_WIDTH;
	rect.h = REWARD_BUBBLE_HEIGHT;
	return rect;
}

void Reward::animate()
{
	spriteColumn_ = int((SDL_GetTicks() / REWARD_FRAME_TIME) % REWARD_ANIMATION_FRAMES);
}
