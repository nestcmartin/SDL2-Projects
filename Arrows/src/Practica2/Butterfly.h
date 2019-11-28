#ifndef __BUTTERFLY_H__
#define __BUTTERFLY_H__

#include "ArrowsGameObject.h"

class Game;
class Butterfly : public ArrowsGameObject
{
private:
	Uint32 spriteRow_;
	Uint32 spriteColumn_;
	Uint32 lastTime_;
	bool dead_;

public:
	Butterfly(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
	virtual ~Butterfly();

	virtual void update();
	virtual void render() const;
	virtual void saveToFile(std::ofstream& stream);
	virtual void loadFromFile(std::ifstream& stream);

private:
	void animate();
};

#endif // !__BUTTERFLY_H__

