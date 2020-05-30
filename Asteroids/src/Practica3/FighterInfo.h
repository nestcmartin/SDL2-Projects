#ifndef __FIGHTER_INFO_H__
#define __FIGHTER_INFO_H__

#include <cstring>

#include "Component.h"

struct FighterInfo : Component {

	FighterInfo(uint8_t fighterId) :
		Component(ECS::FighterInfo), fighterId_(fighterId)
	{

	}

	uint8_t fighterId_;
};

#endif // !__FIGHTER_INFO_H__
