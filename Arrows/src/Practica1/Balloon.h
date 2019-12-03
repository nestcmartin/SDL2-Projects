#ifndef __BALLOON_H__
#define __BALLOON_H__

#include "Texture.h"
#include "Vector2D.h"

const Uint32 ANIMATION_TIME = 300;
const Uint32 ANIMATION_FRAMES = 6;
const Uint32 FRAME_TIME = ANIMATION_TIME / ANIMATION_FRAMES;

const Uint32 BALLOON_WIDTH = 128;
const Uint32 BALLOON_HEIGHT = 128;
const double BALLOON_MAX_SPEED = 10.0;
const double BALLOON_MIN_SPEED = 3.0;
const Vector2D BALLOON_DIR = { 0, - 1 };

class SDLApplication;
class Balloon
{
private:
	SDLApplication* game_;
	Texture* texture_;
	Point2D position_;
	Vector2D direction_;

	Uint32 width_;
	Uint32 height_;

	double speed_;

	Uint32 spriteRow_;
	Uint32 spriteColumn_;

	bool burst_;
	Uint32 burstTime_;

public:
	Balloon(SDLApplication* _g, Texture* _t, Point2D _p, 
		Uint32 _w = BALLOON_WIDTH, Uint32 _h = BALLOON_HEIGHT, double _s = 0.0);
	~Balloon();

	inline bool hasBurst() const { return burst_; }
	SDL_Rect getRect() const;

	bool update();
	void render() const;

	void saveState(std::ofstream& stream);
	void loadState(std::ifstream& stream);
};

#endif // !__BALLOON_H__
