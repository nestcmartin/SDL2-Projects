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
}

#endif // !__MESSAGES_H__