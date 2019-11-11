#ifndef __SCORE_BOARD_H__
#define __SCORE_BOARD_H__

#include "GameObject.h"
#include "Texture.h"

class Game;
class ScoreBoard : public GameObject
{
public:
	ScoreBoard(Game* g, Texture* arrowTexture, Texture* digitsTexture);
	virtual ~ScoreBoard();

	virtual void update();
	virtual void render() const;

	inline int getScore() const { return score_; }
	inline int getArrowsLeft() const { return arrowsLeft_; }
	inline void setScore(int s) { score_ = s; }
	inline void setArrowsLeft(int a) { arrowsLeft_ = a; }

private:
	Game* game_;
	Texture* arrowsSprite_;
	Texture* digitsSprite_;
	int arrowsLeft_;
	int score_;
};

#endif // !__SCORE_BOARD_H__