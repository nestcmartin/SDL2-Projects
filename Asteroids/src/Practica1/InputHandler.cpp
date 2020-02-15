#include "InputHandler.h"

std::unique_ptr<InputHandler> InputHandler::instance_;

InputHandler::InputHandler()
{
	clearState();
	kbState_ = SDL_GetKeyboardState(0);
}

InputHandler::~InputHandler()
{
}

void InputHandler::update(bool& exit)
{
	SDL_Event event;

	clearState();

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;

		case SDL_KEYUP:
			onKeyUp(event);
			break;

		case SDL_MOUSEMOTION:
			onMouseMotion(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonChange(event, true);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonChange(event, false);
			break;

		case SDL_QUIT:
			exit = true;
			break;
		}
	}
}

void InputHandler::clearState()
{
	isKeyUpEvent_ = false;
	isKeyDownEvent_ = false;
	isMouseButtonEvent_ = false;
	isMouseMotionEvent_ = false;

	for (int i = 0; i < 3; i++) mbState_[i] = false;
}

inline void InputHandler::onMouseButtonChange(SDL_Event& event, bool isDown)
{
	isMouseButtonEvent_ = true;
	if (event.button.button == SDL_BUTTON_LEFT) mbState_[LEFT] = isDown;
	else if (event.button.button == SDL_BUTTON_MIDDLE) mbState_[MIDDLE] = isDown;
	else if (event.button.button == SDL_BUTTON_RIGHT) mbState_[RIGHT] = isDown;
}

inline void InputHandler::onMouseMotion(SDL_Event& event)
{
	isMouseMotionEvent_ = true;
	mousePos_.set(event.motion.x, event.motion.y);
}
