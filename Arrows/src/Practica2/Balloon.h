#ifndef __BALLOON_H__
#define __BALLOON_H__

#include "ArrowsGameObject.h"

class Game;
class Balloon : public ArrowsGameObject
{
public:
	static int count;

private:
	bool burst_;
	Uint32 burstTime_;
	Uint32 spriteRow_;
	Uint32 spriteColumn_;

	std::list<Balloon*>::iterator balloonIt_;

public:
	Balloon(Game* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
	virtual ~Balloon();

	virtual void update();
	virtual void render() const;
	virtual void saveToFile(std::ofstream& stream);
	virtual void loadFromFile(std::ifstream& stream);

	inline bool hasBurst() const { return burst_; }

	void setBalloonIterator(std::list<Balloon*>::iterator it) { balloonIt_ = it; }

private:
	void checkBurst();
	void animate();
};

#endif // !__BALLOON_H__
