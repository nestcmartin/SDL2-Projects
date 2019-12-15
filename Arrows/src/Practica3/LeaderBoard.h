#ifndef __LEADER_BOARD_H__
#define __LEADER_BOARD_H__

#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Constants.h"
#include "GameObject.h"

class SDLApplication;
class LeaderBoard : public GameObject
{
	struct ScoreRegister 
	{
		int score;
		std::string name;
		ScoreRegister() : name(""), score(0) {}
		ScoreRegister(std::string n, int s) : name(n), score(s) {}
	};
	struct ScoreComparer
	{
		bool operator()(const ScoreRegister& rhs, const ScoreRegister& lhs) const
		{
			return lhs.score < rhs.score;
		}
	};

private:
	std::vector<ScoreRegister> leaderBoard_;

	SDLApplication* app_;

public:
	LeaderBoard(SDLApplication* a);
	~LeaderBoard();

	virtual void update();
	virtual void render() const;

	void registerPlayerScore(int score);

private:
	void saveLeaderBoard();
	void loadLeaderBoard();
};

#endif // !__LEADER_BOARD_H__