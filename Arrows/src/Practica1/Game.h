#ifndef __GAME_H__
#define __GAME_H__

#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"
#include "ScoreBoard.h"
#include "SDLError.h"

const Uint32 FRAME_RATE = 16;
const Uint32 WIN_WIDTH = 1280;
const Uint32 WIN_HEIGHT = 720;
const Uint32 NUM_TEXTURES = 8;

const Uint32 NUM_ARROWS = 10;
const Uint32 SPAWN_TIME = 200;
const Uint32 SPAWN_LOWER_BOUND = WIN_WIDTH / 3;
const Uint32 SPAWN_UPPER_BOUND = WIN_WIDTH - BALLOON_WIDTH;
const Uint32 SPAWN_SPACE = SPAWN_UPPER_BOUND - SPAWN_LOWER_BOUND;

const std::string STATE_FILE = "state.txt";
const std::string IMAGE_PATH = "..\\res\\images\\";

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
	Bow* bow;
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	ScoreBoard* scoreBoard_;

	bool end_;
	bool exit_;
	int score_;
	int arrowsLeft;
	Uint32 lastSpawnTime_;

	std::vector<Arrow*> arrows;
	std::vector<Balloon*> balloons;
	Texture* textures[NUM_TEXTURES];

public:
	Game();
	~Game();

	inline Uint32 getScore() const { return score_; }
	inline Uint32 getArrowsLeft() const { return arrowsLeft; }
	inline bool hasArrows() const { return arrowsLeft > 0; }
	Texture* getTexture(TextureName i) const { return textures[i]; }

	void run();
	void shootArrow(Arrow* a);
	bool checkCollision(Balloon* b);

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
