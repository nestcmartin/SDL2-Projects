#include "LeaderBoard.h"
#include "SDLApplication.h"


LeaderBoard::LeaderBoard(SDLApplication* a) :
	app_(a)
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
		int w, h;
		std::string s = leaderBoard_[i].name + " - " + std::to_string(leaderBoard_[i].score);
		Texture* t = new Texture(app_->getRenderer(), s, app_->getFont("PAINT22"), { 0, 0, 0, 255 });
		app_->getFont("PAINT22")->sizeOfText(s, w, h);
		t->render({ static_cast<int>((WIN_WIDTH - w) / 2), static_cast<int>(130 + h * i), w, h });
		delete t; t = nullptr;
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
		throw FileNotFoundError("Couldn´t open " + LEADERBOARD_FILE + "\n");

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
		throw FileNotFoundError("Couldn´t open " + LEADERBOARD_FILE + "\n");

	for (int i = 0; i < 10; i++)
	{
		ScoreRegister reg;
		stream >> reg.name >> reg.score;
		leaderBoard_.push_back(reg);
	}

	stream.close();
}