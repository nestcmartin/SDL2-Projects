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

class Game;
class Balloon
{
private:
	Point2D p;
	Vector2D d;
	Vector2D v;
	double s;

	Uint32 w;
	Uint32 h;
	Uint32 r;
	Uint32 c;

	Texture* sprite;
	Game* game;

	bool active;
	bool burst_;
	Uint32 burstTime_;

public:
	Balloon(Game* _g, Texture* _t, Point2D _p, 
		Uint32 _w = BALLOON_WIDTH, Uint32 _h = BALLOON_HEIGHT, double _s = 0.0);
	~Balloon();

	inline bool isActive() const { return active; }

	SDL_Rect getRect() const;

	void update();
	void render() const;

	void saveState(std::ofstream& stream);
	void loadState(std::ifstream& stream);
};

#endif // !__BALLOON_H__
