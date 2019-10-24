#ifndef __GAME_H__
#define __GAME_H__

#include "Constants.h"
#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"
#include "ScoreBoard.h"
#include "SDLError.h"

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
	
	Uint32 score_;
	Uint32 arrowsLeft_;
	Uint32 lastSpawnTime_;

	bool end_;
	bool exit_;

	Bow* bow_;
	ScoreBoard* scoreBoard_;
	std::vector<Arrow*> arrows_;
	std::vector<Balloon*> balloons_;
	std::vector<GameObject*> gameObjects_;

	Texture* textures[NUM_TEXTURES];

public:
	Game();
	~Game();

	inline Uint32 getScore() const { return score_; }
	inline Uint32 getArrowsLeft() const { return arrowsLeft_; }
	inline Texture* getTexture(Game::TextureName i) const { return textures[i]; }

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
