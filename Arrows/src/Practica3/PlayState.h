#ifndef __PLAY_STATE_H__
#define __PLAY_STATE_H__

#include <time.h>

#include "GameState.h"

#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"
#include "ScoreBoard.h"
#include "Butterfly.h"
#include "Reward.h"

class SDLApplication;
class PlayState : public GameState
{
private:
	bool win_;
	bool changeLevel_;
	Uint32 currentLevel_;
	Uint32 lastSpawnTime_;
	Uint32 numButterflies_;

	Bow* bow_;
	ScoreBoard* scoreBoard_;

	std::list<Arrow*> arrows_;
	std::list<Balloon*> balloons_;
	std::list<Butterfly*> butterflies_;
	std::list<Reward*> rewards_;
	std::list<std::list<GameObject*>::iterator> erasableObjects_;

public:
	PlayState(SDLApplication* a);
	virtual ~PlayState();

	virtual std::string getStateName() const { return "PLAY_STATE"; }

	virtual void handleEvents(SDL_Event& event);
	virtual void update();
	virtual void render() const;

	void shootArrow(Arrow* a);
	bool hitBalloon(Balloon* b);
	bool hitButterfly(Butterfly* b);
	bool hitRewardBubble(Reward* b);

	void killArrow(std::list<GameObject*>::iterator it);
	void killBalloon(std::list<GameObject*>::iterator it);
	void killButterfly(std::list<GameObject*>::iterator it);
	void killReward(std::list<GameObject*>::iterator it, std::list<EventHandler*>::iterator eit);
	void killGameObject(std::list<GameObject*>::iterator it);

	void rewardNextLevel();
	void rewardMoreArrows();

	void saveToFile(int code);
	void loadFromFile(int code);

	inline bool isWon() const { return win_; }
	inline int getScore() const { return scoreBoard_->getScore(); }
	inline bool hasArrows() const { return scoreBoard_->getArrowsLeft() != 0; }

private:
	void initScene();
	void clearScene();

	void addArrow(Arrow* a);
	void addBalloon(Balloon* b);
	void addButterfly(Butterfly* b);
	void addRewardBubble(Reward* r);

	void spawnBallon();
	void changeLevel();

	void eraseObjects();
};

#endif // !__PLAY_STATE_H__
