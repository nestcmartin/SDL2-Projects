#ifndef __REWARD_H__
#define __REWARD_H__

#include "ArrowsGameObject.h"
#include "EventHandler.h"

class GameState;
class Reward : public ArrowsGameObject, public EventHandler
{
private:
	Texture* bubbleTexture_;
	bool bubbled_;
	bool used_;
	Uint32 spriteRow_;
	Uint32 spriteColumn_;

public:
	Reward(GameState* g, Texture* t, Texture* bt, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
	virtual ~Reward();

	virtual void update();
	virtual void render() const;
	virtual bool handleEvents(SDL_Event& event);

	virtual void saveToFile(std::ofstream& stream);
	virtual void loadFromFile(std::ifstream& stream);

	virtual SDL_Rect getCollisionRect() const;

private:
	void animate();
};

#endif // !__REWARD_H__