#ifndef __SCORE_BOARD_H__
#define __SCORE_BOARD_H__

#include <vector>
#include <fstream>
#include <iostream>

#include "Texture.h"

const Uint32 UI_ARROW_POS_X = 300;
const Uint32 UI_ARROW_POS_Y = 40;
const Uint32 UI_ARROW_WIDTH = 20;
const Uint32 UI_ARROW_HEIGHT = 65;
const Uint32 UI_SCORE_POS_X = 200;
const Uint32 UI_SCORE_POS_Y = 40;
const Uint32 UI_SCORE_WIDTH = 27;
const Uint32 UI_SCORE_HEIGHT = 65;

const std::string BOARD_FILE = "leaderboard.txt";

class SDLApplication;
class ScoreBoard
{
	struct ScoreRegister 
	{
		std::string name;
		Uint32 score;
		ScoreRegister() : name(""), score(0) {}
		ScoreRegister(std::string n, Uint32 s) : name(n), score(s) {}

		std::ostream& operator<<(std::ostream& out)
		{
			out << name << " " << score << std::endl;
			return out;
		}

		std::istream& operator>>(std::istream& in)
		{
			in >> name >> score;
			return in;
		}
	};
	struct ScoreComparer
	{
		bool operator()(const ScoreRegister& rhs, const ScoreRegister& lhs) const
		{
			return lhs.score < rhs.score;
		}
	};

private:
	SDLApplication* game_;
	Texture* arrowsSprite_;
	Texture* digitsSprite_;

	Uint32 score_;
	Uint32 arrowsLeft_;

	std::vector<ScoreRegister> leaderBoard;

public:
	ScoreBoard(SDLApplication* _g, Texture* _arrowT, Texture* _digitsT);
	~ScoreBoard();

	void registerPlayerScore();

	void update();
	void render() const;

private:
	void saveLeaderBoard();
	void loadLeaderBoard();

};


#endif // !__SCORE_BOARD_H__
