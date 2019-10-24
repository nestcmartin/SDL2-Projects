#ifndef __BOW_H__
#define __BOW_H__

#include "Arrow.h"

class Game;
class Bow : public GameObject
{
private:
	Arrow* arrow_;
	Uint32 drawTime_;

	bool armed_;

	void charge();
	void loose();

public:
	Bow(Game* g, Texture* t, Point2D p);
	~Bow();

	inline bool isArmed() const { return armed_; }
	inline void setArmed(bool a) { armed_ = a; }

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;

	virtual void saveState(std::ofstream& stream);
	virtual void loadState(std::ifstream& stream);
};

#endif // !__BOW_H__
