#ifndef __GAME_H__
#define __GAME_H__

#include <time.h>

#include "SDLError.h"
#include "Constants.h"

#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"
#include "ScoreBoard.h"
#include "LeaderBoard.h"
#include "Butterfly.h"
#include "Reward.h"

class Game
{
	struct TextureAttributes {
		std::string filename;
		Uint32 numRows;
		Uint32 numCols;
	};

	const TextureAttributes textureAttributes[NUM_TEXTURES] = {
		{"Arrow1.png",				 1,  1},
		{"Arrow2.png",				 1,  1},
		{"balloons.png",			 7,  6},
		{"bg_spring_trees_1.png",    1,  1},
		{"bg1.png",					 1,  1},
		{"Bow1.png",				 1,  1},
		{"Bow2.png",				 1,  1},
		{"bubble.png",				 1,  1},
		{"butterfly2.png",			 4, 10},
		{"Cartoon_Forest_BG_01.png", 1,  1},
		{"Cartoon_Forest_BG_02.png", 1,  1},
		{"Cartoon_Forest_BG_03.png", 1,  1},
		{"Cartoon_Forest_BG_04.png", 1,  1},
		{"digits1.png",				 1, 10},
		{"gameover.png",			 1,  1},
		{"rewards.png",				10,  8},
		{"menu.png",				 1,  1}
	};

public:
	enum TextureName {
		ARROW,
		ARROW_UI,
		BALLOONS,
		BACKGROUND_SPRING,
		BACKGROUND_AUTUMN,
		ARMED_BOW,
		BOW,
		BUBBLE,
		BUTTERFLY,
		BACKGROUND_1,
		BACKGROUND_2,
		BACKGROUND_3,
		BACKGROUND_4,
		DIGITS,
		GAME_OVER,
		REWARDS,
		MENU
	};

	enum GameState { MENU_STATE, PLAY_STATE, END_STATE };

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	Bow* bow_;
	ScoreBoard* scoreBoard_;
	LeaderBoard* leaderBoard_;
	
	Texture* textures_[NUM_TEXTURES];
	std::list<Arrow*> arrows_;
	std::list<Balloon*> balloons_;
	std::list<Reward*> rewards_;
	std::list<Butterfly*> butterflies_;
	std::list<EventHandler*> eventHandlers_;
	std::list<GameObject*> gameObjects_;
	std::list<std::list<GameObject*>::iterator> erasableObjects_;

	bool exit_;
	bool changeLevel_;
	Uint32 currentLevel_;
	Uint32 lastSpawnTime_;
	GameState currentState_;

public:
	Game();
	~Game();

	void run();

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

	bool hasArrows() { return scoreBoard_->getArrowsLeft() != 0; }
	Texture* getTexture(TextureName i) const { return textures_[i]; }

private:
	void initSDL();
	void loadTextures();
	void loadEntities();
	void clearScene();
	void clearTextures();
	void closeSDL();

	void addArrow(Arrow* a);
	void addBalloon(Balloon* b);
	void addButterfly(Butterfly* b);
	void addRewardBubble(Reward* r);
	void addEventHandler(EventHandler* e);
	void addGameObject(ArrowsGameObject* o);

	void spawnBallon();
	void changeLevel();

	void handleEvents();
	void update();
	void render() const;

	void saveState();
	void loadState();

	void eraseObjects();
};

#endif // !__GAME_H__
