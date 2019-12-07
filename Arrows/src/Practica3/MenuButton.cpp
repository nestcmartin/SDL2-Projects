#include "MenuButton.h"

MenuButton::MenuButton(GameState* g, Texture* t, Uint32 w, Uint32 h, Point2D p, SDLApplication* a, CallBackOnClick* cb) :
	SDLGameObject(g, t, w, h, p),
	EventHandler(),
	app_ (a),
	callbackOnClick_(cb),
	currentState_(MOUSE_OUT)
{
}

MenuButton::~MenuButton()
{
}

bool MenuButton::handleEvents(SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = { event.button.x, event.button.y };
			if (SDL_PointInRect(&p, &getDestRect()))
			{
				currentState_ = MOUSE_CLICKED;
				return true;
			}
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = { event.button.x, event.button.y };
			if (SDL_PointInRect(&p, &getDestRect()))
			{
				currentState_ = MOUSE_OVER;
				callbackOnClick_(app_);
				return true;
			}
		}
	}

	if (event.type == SDL_MOUSEMOTION)
	{
		SDL_Point p = { event.motion.x, event.motion.y };
		if (SDL_PointInRect(&p, &getDestRect()))
		{
			currentState_ = MOUSE_OVER;
			return true;
		}		
		currentState_ = MOUSE_OUT;
	}

	return false;
}

void MenuButton::update()
{
	return;
}

void MenuButton::render() const
{
	SDL_Rect destRect = getDestRect();
	texture_->renderFrame(destRect, 0, currentState_, 0);
}