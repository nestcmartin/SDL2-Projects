#ifndef __BOW_H__
#define __BOW_H__

#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "Arrow.h"

class GameState;
class Bow : public ArrowsGameObject, public EventHandler
{
private:
	bool armed_;
	Arrow* arrow_;
	Uint32 drawTime_;

public:
	Bow(GameState* g, Texture* t, Uint32 w, Uint32 h, Point2D p, Vector2D d, double s, int a);
	virtual ~Bow();

	virtual void update();
	virtual void render() const;
	virtual bool handleEvents(SDL_Event& event);

	inline bool isArmed() const { return armed_; }

private:
	void charge();
	void loose();
};

#endif // !__BOW_H__
