#ifndef __SDL_APPLICATION_H__
#define __SDL_APPLICATION_H__

#include <time.h>

#include "SDLError.h"
#include "GameStateMachine.h"

class SDLApplication
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

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	Texture* textures_[NUM_TEXTURES];
	GameStateMachine* gameStateMachine_;

	bool exit_;
	bool error_;

public:
	SDLApplication();
	~SDLApplication();

	void run();

	Texture* getTexture(TextureName i) const { return textures_[i]; }

private:
	void handleEvents();
	void update();
	void render() const;
};

#endif // !__SDL_APPLICATION_H__