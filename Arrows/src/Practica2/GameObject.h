#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "Texture.h"
#include "Vector2D.h"

class Game;
class GameObject
{
protected:
	Game* game_;
	Texture* sprite_;
	Point2D position_;
	Vector2D direction_;
	Uint32 width_;
	Uint32 height_;

	int angle_;
	double speed_;
	bool active_;

	Uint32 spriteRow_;
	Uint32 spriteCol_;

public:
	GameObject(Game* g, Texture* t, Point2D p, Vector2D d, Uint32 w, Uint32 h, int a, double s);
	~GameObject();

	inline bool isActive() const { return active_; }
	inline void setActive(bool a) { active_ = a; }

	SDL_Rect getRect() const;

	virtual void handleEvents(SDL_Event& e);
	virtual void update();
	virtual void render() const;

	virtual void saveState(std::ostream& out);
	virtual void loadState(std::istream& in);
};

#endif // !__GAME_OBJECT_H__