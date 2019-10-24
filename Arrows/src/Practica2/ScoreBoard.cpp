#include "ScoreBoard.h"
#include "Game.h"

#include <algorithm>

ScoreBoard::ScoreBoard(Game* _g, Texture* _arrowT, Texture* _digitsT) :
	game(_g),
	arrowsSprite(_arrowT),
	digitsSprite(_digitsT),
	score(0),
	arrowsLeft(NUM_ARROWS)
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
	leaderBoard.push_back({ name, score });
	std::sort(leaderBoard.begin(), leaderBoard.end(), ScoreComparer());

	saveLeaderBoard();
}

void ScoreBoard::update()
{
	score = game->getScore();
	arrowsLeft = game->getArrowsLeft();
}

void ScoreBoard::render() const
{
	for (Uint32 i = 0; i < arrowsLeft; i++)
	{
		arrowsSprite->render({ static_cast<int>(UI_ARROW_POS_X + (UI_ARROW_WIDTH * i)),
							   static_cast<int>(UI_ARROW_POS_Y),
							   UI_ARROW_WIDTH, UI_ARROW_HEIGHT });
	}

	Uint32 centenas = score / 100;
	Uint32 decenas = (score % 100) / 10;
	Uint32 unidades = (score % 10);

	digitsSprite->renderFrame({ static_cast<int>(UI_SCORE_POS_X + (UI_SCORE_WIDTH * 0)),
								static_cast<int>(UI_SCORE_POS_Y),
								UI_SCORE_WIDTH, UI_SCORE_HEIGHT },
								0, centenas);
	digitsSprite->renderFrame({ static_cast<int>(UI_SCORE_POS_X + (UI_SCORE_WIDTH * 1)),
								static_cast<int>(UI_SCORE_POS_Y),
								UI_SCORE_WIDTH, UI_SCORE_HEIGHT },
								0, decenas);
	digitsSprite->renderFrame({ static_cast<int>(UI_SCORE_POS_X + (UI_SCORE_WIDTH * 2)),
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

