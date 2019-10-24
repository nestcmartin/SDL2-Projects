#ifndef __ARROW_H__
#define __ARROW_H__

#include "Vector2D.h"
#include "Texture.h"

const Uint32 ARROW_WIDTH = 130;
const Uint32 ARROW_HEIGHT = 20;
const double ARROW_SPEED = 20.0;

class Arrow
{
private:
	Point2D p;
	Vector2D d;
	Vector2D v;
	double s;
	int a;

	Uint32 w;
	Uint32 h;

	Texture* sprite;

	bool active;

public:
	Arrow(Texture* _t, Point2D _p, 
		Uint32 _w = ARROW_WIDTH, Uint32 _h = ARROW_HEIGHT, double _s = ARROW_SPEED, int _a = 0);
	~Arrow();

	inline bool isActive() const { return active; }

	SDL_Rect getArrowhead() const;
	SDL_Rect getRect() const;

	void update();
	void render() const;

	void saveState(std::ofstream& stream);
	void loadState(std::ifstream& stream);
};



#endif // !__ARROW_H__
