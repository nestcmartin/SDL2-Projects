#ifndef __ARROW_H__
#define __ARROW_H__

#include "Vector2D.h"
#include "Texture.h"

const Uint32 ARROW_WIDTH = 130;
const Uint32 ARROW_HEIGHT = 20;
const double ARROW_SPEED = 20.0;
const Vector2D ARROW_DIR = { 1, 0 };

class Arrow
{
private:
	Texture* texture_;
	Point2D position_;
	Vector2D direction_;

	Uint32 width_;
	Uint32 height_;

	double speed_;
	int angle_;

public:
	Arrow(Texture* _t, Point2D _p, Uint32 _w = ARROW_WIDTH, 
		Uint32 _h = ARROW_HEIGHT, double _s = ARROW_SPEED, int _a = 0);
	~Arrow();

	SDL_Rect getArrowhead() const;
	SDL_Rect getRect() const;

	bool update();
	void render() const;
	void saveState(std::ofstream& stream);
	void loadState(std::ifstream& stream);
};



#endif // !__ARROW_H__
