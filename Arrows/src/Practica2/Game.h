#ifndef __GAME_H__
#define __GAME_H__

#include "SDLError.h"
#include "Constants.h"

#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"
#include "ScoreBoard.h"
#include "LeaderBoard.h"

class Game
{
	struct TextureAttributes {
		std::string filename;
		Uint32 numRows;
		Uint32 numCols;
	};
	const TextureAttributes textureAttributes[NUM_TEXTURES] = {
		{"Arrow1.png",   1,  1},
		{"Arrow2.png",   1,  1},
		{"balloons.png", 7,  6},
		{"bg1.png",      1,  1},
		{"Bow1.png",     1,  1},
		{"Bow2.png",     1,  1},
		{"digits1.png",  1, 10},
		{"gameover.png", 1,  1}
	};

public:
	enum TextureName {
		ARROW,
		ARROW_UI,
		BALLOONS,
		BACKGROUND,
		ARMED_BOW,
		BOW,
		DIGITS,
		GAME_OVER
	};

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	Bow* bow_;
	ScoreBoard* scoreBoard_;
	LeaderBoard* leaderBoard_;
	
	Texture* textures_[NUM_TEXTURES];
	std::list<Arrow*> arrows_;
	std::list<Balloon*> balloons_;
	std::list<EventHandler*> eventHandlers_;
	std::list<ArrowsGameObject*> gameObjects_;

	bool end_;
	bool exit_;
	Uint32 lastSpawnTime_;

public:
	Game();
	~Game();

	void run();
	void shootArrow(Arrow* a);
	bool checkCollision(Balloon* b);
	void addGameObject(ArrowsGameObject* o);

	bool hasArrows() { return scoreBoard_->getArrowsLeft() != 0; }
	Texture* getTexture(TextureName i) const { return textures_[i]; }


private:
	void initSDL();
	void loadTextures();
	void loadEntities();
	void clearScene();
	void clearTextures();
	void closeSDL();

	void spawnBallon();

	void handleEvents();
	void update();
	void render() const;

	void saveState();
	void loadState();
};

#endif // !__GAME_H__
