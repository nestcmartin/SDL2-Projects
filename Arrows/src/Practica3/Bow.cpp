#include "Bow.h"
#include "GameState.h"

Bow::Bow(GameState* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a) :
	ArrowsGameObject(g, t, w, h, p, d, s, a),
	EventHandler(),
	armed_(false),
	arrow_(nullptr),
	drawTime_(0)
{
}

Bow::~Bow()
{
}

bool Bow::handleEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_LEFT) charge();
		else if (event.key.keysym.sym == SDLK_RIGHT) loose();
		else if (event.key.keysym.sym == SDLK_UP) direction_ = Vector2D(0, -1);
		else if (event.key.keysym.sym == SDLK_DOWN) direction_ = Vector2D(0, 1);
		else if (event.key.keysym.sym == SDLK_a) angle_ -= BOW_ANGLE_INCREMENT;
		else if (event.key.keysym.sym == SDLK_d) angle_ += BOW_ANGLE_INCREMENT;
		return true;
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP ||
			event.key.keysym.sym == SDLK_DOWN)
		{
			direction_ = Vector2D(0, 0);
		}
		return true;
	}
	return false;
}

void Bow::update()
{	
	// Limit y-axis movement
	if ((position_ + (direction_ * speed_)).getY() < 0.0 ||
		(position_ + (direction_ * speed_)).getY() > (WIN_HEIGHT - BOW_HEIGHT)) return;

	// Limit rotation
	if (angle_ > BOW_ANGLE_LIMIT) angle_ = BOW_ANGLE_LIMIT;
	if (angle_ < -BOW_ANGLE_LIMIT) angle_ = -BOW_ANGLE_LIMIT;
	
	ArrowsGameObject::update();
}

void Bow::render() const
{
	ArrowsGameObject::render();

	if (armed_)
	{
		/*game_->getTexture(SDLApplication::ARROW)->renderFrame(
			{ static_cast<int>(position_.getX()), 
			  static_cast<int>(position_.getY() + (height_ / 2)), 
			  ARROW_WIDTH, ARROW_HEIGHT }, 0, 0, angle_);*/
	}
}

void Bow::charge()
{
	/*if (!armed_ && game_->hasArrows())
	{
		drawTime_ = SDL_GetTicks();
		armed_ = true;
	}*/
}

void Bow::loose()
{
	if (armed_)
	{
		/*double drawFactor = 1.0 + ((SDL_GetTicks() - drawTime_) / 10000.0);
		arrow_ = new Arrow(game_, game_->getTexture(SDLApplication::ARROW), ARROW_WIDTH, ARROW_HEIGHT,
			{ position_.getX(), position_.getY() + (height_ / 2) }, ARROW_DIR, ARROW_SPEED * drawFactor, angle_);
		game_->shootArrow(arrow_);
		armed_ = false;*/
	}
}