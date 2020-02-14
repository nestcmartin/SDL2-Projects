#pragma once

#include "Component.h"
#include "Transform.h"

class PaddleKBCtrl: public Component {
public:
	PaddleKBCtrl();
	PaddleKBCtrl(SDL_Keycode up, SDL_Keycode down, SDL_Keycode stop);
	virtual ~PaddleKBCtrl();

	inline void setCtrlKeys(SDL_Keycode up, SDL_Keycode down,
			SDL_Keycode stop) {
		up_ = up;
		down_ = down;
		stop_ = stop;
	}

	void init() override;
	void update() override;

private:
	SDL_Keycode up_;
	SDL_Keycode down_;
	SDL_Keycode stop_;
	Transform *tr_;
};

