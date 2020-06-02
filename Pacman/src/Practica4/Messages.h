#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <ctime>

class Entity;

namespace msg 
{
	using MessageType = std::size_t;

	enum MessageId : MessageType 
	{
		_GAME_START, 
		_GAME_OVER,
		_FOOD_COLLISION,
		_GHOST_COLLISION,
		_PACMAN_WIN,
		_PACMAN_LOSE,
		_RESET,

		// 
		_last_MsgId_
	};

	struct Message
	{
		Message(MessageId id) :
			id(id) 
		{
		}

		MessageId id;
	};

	struct FoodCollisionMsg : Message
	{
		FoodCollisionMsg(Entity* e) :
			Message(msg::_FOOD_COLLISION),
			e(e)
		{
		}

		Entity* e;
	};

	struct GhostCollisionMsg : Message
	{
		GhostCollisionMsg(Entity* e) :
			Message(msg::_GHOST_COLLISION),
			e(e)
		{
		}

		Entity* e;
	};
}

#endif // !__MESSAGES_H__