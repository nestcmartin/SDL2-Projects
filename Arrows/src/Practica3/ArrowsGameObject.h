#ifndef __ARROWS_GAME_OBJECT_H__
#define __ARROWS_GAME_OBJECT_H__

#include <list>
#include <fstream>

#include "SDLGameObject.h"
#include "FileFormatError.h"

class GameState;
class ArrowsGameObject : public SDLGameObject
{
protected:
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

	virtual SDL_Rect getCollisionRect() const;

	void setIteratorList(const std::list<GameObject*>::iterator& it);

protected:
	ArrowsGameObject(GameState* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
};

#endif // !__ARROWS_GAME_OBJECT_H__
