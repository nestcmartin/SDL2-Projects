#ifndef __BOW_H__
#define __BOW_H__

#include "Arrow.h"

const Uint32 BOW_WIDTH = 100;
const Uint32 BOW_HEIGHT = 150;
const Uint32 ARMED_BOW_WIDTH = 100;
const Uint32 ARMED_BOW_HEIGHT = 150;
const double BOW_SPEED = 10.0;

class SDLApplication;
class Bow
{
private:
	SDLApplication* game_;
	Texture* texture_;
	Point2D position_;
	Vector2D direction_;

	Uint32 width_;
	Uint32 height_;

	int angle_;
	double speed_;

	Arrow* arrow_;

	bool armed_;
	Uint32 drawTime_;

	void charge();
	void loose();

public:
	Bow(SDLApplication* _g, Texture* _t, Point2D _p, 
		Uint32 _w = BOW_WIDTH, Uint32 _h = BOW_HEIGHT, double _s = BOW_SPEED);
	~Bow();

	inline bool isArmed() const { return armed_; }
	SDL_Rect getRect() const;

	void handleEvents(SDL_Event& event);
	void update();
	void render() const;
	void saveState(std::ofstream& stream);
	void loadState(std::ifstream& stream);
};

#endif // !__BOW_H__
