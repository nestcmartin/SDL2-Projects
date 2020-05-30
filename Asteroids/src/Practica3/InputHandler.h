#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <array>
#include <memory>
#include <SDL.h>

#include "Vector2D.h"

class InputHandler
{
private:
	// Singleton
	static std::unique_ptr<InputHandler> instance_;

	// Keyboard State
	const Uint8* kbState_;
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	bool isMouseMotionEvent_;
	bool isMouseButtonEvent_;

	// Mouse State
	Vector2D mousePos_;
	std::array<bool, 3> mbState_;

public:
	enum MouseButton : Uint8
	{
		LEFT = 0,
		MIDDLE = 1,
		RIGHT = 2
	};

	InputHandler(InputHandler&) = delete;
	InputHandler& operator=(InputHandler&) = delete;
	virtual ~InputHandler();

	inline static InputHandler* instance()
	{
		if (!instance_.get()) instance_.reset(new InputHandler());
		return instance_.get();
	}

	void update(bool& exit);

	// Keyboard
	inline bool keyDownEvent() { return isKeyDownEvent_; }
	inline bool keyUpEvent() { return isKeyUpEvent_; }
	inline bool isKeyDown(SDL_Scancode key) { return keyDownEvent() && kbState_[key] == 1; }
	inline bool isKeyDown(SDL_Keycode key) { return isKeyDown(SDL_GetScancodeFromKey(key)); }
	inline bool isKeyUp(SDL_Scancode key) { return keyUpEvent() && kbState_[key] == 0; }
	inline bool isKeyUp(SDL_Keycode key) { return isKeyUp(SDL_GetScancodeFromKey(key)); }

	// Mouse
	inline bool mouseMotionEvent() { return isMouseMotionEvent_; }
	inline bool mouseButtonEvent() { return isMouseButtonEvent_; }
	inline const Vector2D& getMousePos() { return mousePos_; }
	inline int getMouseButtonState(MouseButton b) { return mbState_[b]; }

private:
	InputHandler();
	void clearState();

	inline void onKeyDown(SDL_Event &event) 
	{
		isKeyDownEvent_ = true;
	}

	inline void onKeyUp(SDL_Event &event) 
	{
		isKeyUpEvent_ = true;
	}

	inline void onMouseMotion(SDL_Event &event) 
	{
		isMouseMotionEvent_ = true;
		mousePos_.set(event.motion.x, event.motion.y);
	}

	inline void onMouseButtonChange(SDL_Event &event, bool isDown) 
	{
		isMouseButtonEvent_ = true;
		if (event.button.button == SDL_BUTTON_LEFT) mbState_[LEFT] = isDown;
		else if (event.button.button == SDL_BUTTON_MIDDLE) mbState_[MIDDLE] = isDown;
		else if (event.button.button == SDL_BUTTON_RIGHT) mbState_[RIGHT] = isDown;
	}
};

#endif // !__INPUT_HANDLER_H__