#include "ScoreBoard.h"
#include "Game.h"

#include <algorithm>

ScoreBoard::ScoreBoard(Game* _g, Texture* _arrowT, Texture* _digitsT) :
	game_(_g),
	arrowsSprite_(_arrowT),
	digitsSprite_(_digitsT),
	score_(0),
	arrowsLeft_(NUM_ARROWS)
{
	loadLeaderBoard();
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::registerPlayerScore()
{
	std::string name = "";
	std::cout << "Introduce tu nombre: "; std::cin >> name;
	leaderBoard.push_back({ name, score_ });
	std::sort(leaderBoard.begin(), leaderBoard.end(), ScoreComparer());

	saveLeaderBoard();
}

void ScoreBoard::update()
{
	score_ = game_->getScore();
	arrowsLeft_ = game_->getArrowsLeft();
}

void ScoreBoard::render() const
{
	for (Uint32 i = 0; i < arrowsLeft_; i++)
	{
		arrowsSprite_->render({ static_cast<int>(UI_ARROW_POS_X + (UI_ARROW_WIDTH * i)),
							   static_cast<int>(UI_ARROW_POS_Y),
							   UI_ARROW_WIDTH, UI_ARROW_HEIGHT });
	}

	Uint32 centenas = score_ / 100;
	Uint32 decenas = (score_ % 100) / 10;
	Uint32 unidades = (score_ % 10);

	digitsSprite_->renderFrame({ static_cast<int>(UI_SCORE_POS_X + (UI_SCORE_WIDTH * 0)),
								static_cast<int>(UI_SCORE_POS_Y),
								UI_SCORE_WIDTH, UI_SCORE_HEIGHT },
								0, centenas);
	digitsSprite_->renderFrame({ static_cast<int>(UI_SCORE_POS_X + (UI_SCORE_WIDTH * 1)),
								static_cast<int>(UI_SCORE_POS_Y),
								UI_SCORE_WIDTH, UI_SCORE_HEIGHT },
								0, decenas);
	digitsSprite_->renderFrame({ static_cast<int>(UI_SCORE_POS_X + (UI_SCORE_WIDTH * 2)),
								static_cast<int>(UI_SCORE_POS_Y),
								UI_SCORE_WIDTH, UI_SCORE_HEIGHT },
								0, unidades);
}

void ScoreBoard::saveLeaderBoard()
{
	std::ofstream stream;
	stream.open(BOARD_FILE);
	if (!stream.is_open()) throw FileNotFoundError("Couldn´t open leaderboard.txt\n");

	for (int i = 0; i < 10; i++)
	{
		std::cout << leaderBoard[i].name << ":\t" << leaderBoard[i].score << "\n";
		stream << leaderBoard[i].name << " " << leaderBoard[i].score << "\n";
	}

	stream.close();
}

void ScoreBoard::loadLeaderBoard()
{
	std::ifstream stream;
	stream.open(BOARD_FILE);
	if (!stream.is_open()) throw FileNotFoundError("Couldn´t open leaderboard.txt\n");

	for (int i = 0; i < 10; i++)
	{
		ScoreRegister reg;
		stream >> reg.name >> reg.score;
		leaderBoard.push_back(reg);
	}

	stream.close();
}

