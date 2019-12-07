#include "LeaderBoard.h"

LeaderBoard::LeaderBoard()
{
}

LeaderBoard::~LeaderBoard()
{
}

void LeaderBoard::update()
{
	loadLeaderBoard();
}

void LeaderBoard::render() const
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << leaderBoard_[i].name << ":\t" << leaderBoard_[i].score << "\n";
	}
}

void LeaderBoard::registerPlayerScore(int score)
{
	std::string name;
	std::cout << "Introduce tu nombre: "; 
	std::cin >> name;

	leaderBoard_.push_back({ name.substr(0, 6), score });
	std::sort(leaderBoard_.begin(), leaderBoard_.end(), ScoreComparer());

	saveLeaderBoard();
}

void LeaderBoard::saveLeaderBoard()
{
	std::ofstream stream;
	stream.open(LEADERBOARD_FILE);
	if (!stream.is_open()) 
		throw FileNotFoundError("Couldn´t open leaderboard.txt\n");

	for (int i = 0; i < 10; i++)
	{
		stream << leaderBoard_[i].name << " " << leaderBoard_[i].score << "\n";
	}

	stream.close();
}

void LeaderBoard::loadLeaderBoard()
{
	std::ifstream stream;
	stream.open(LEADERBOARD_FILE);
	if (!stream.is_open()) 
		throw FileNotFoundError("Couldn´t open leaderboard.txt\n");

	for (int i = 0; i < 10; i++)
	{
		ScoreRegister reg;
		stream >> reg.name >> reg.score;
		leaderBoard_.push_back(reg);
	}

	stream.close();
}