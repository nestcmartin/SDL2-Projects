#ifndef __ARROWS_GAME_OBJECT_H__
#define __ARROWS_GAME_OBJECT_H__

#include <list>

#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

class SDLApplication;
class ArrowsGameObject : public GameObject
{
protected:
	SDLApplication* game_;
	Texture* texture_;
	Uint32 width_;
	Uint32 height_;
	Point2D position_;
	Vector2D direction_;
	double speed_;
	int angle_;

	std::list<GameObject*>::iterator iterator_;

public:
	virtual ~ArrowsGameObject();

	virtual void update();
	virtual void render() const;

	virtual void saveToFile(std::ofstream& stream);
	virtual void loadFromFile(std::ifstream& stream);

	virtual SDL_Rect getDestRect() const;
	virtual SDL_Rect getCollisionRect() const;

	void setIteratorList(const std::list<GameObject*>::iterator& it);

protected:
	ArrowsGameObject(SDLApplication* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
};

#endif // !__ARROWS_GAME_OBJECT_H__
