#ifndef __ECS_H__
#define __ECS_H__

#include <ctime>

namespace ECS
{
	using ComponentId = std::size_t;
	using GroupId = std::size_t;
	using HandlerId = std::size_t;
	using SystemId = std::size_t;

	enum CmpId : ComponentId 
	{
		Transform = 0,
		ImageComponent,
		AnimatedImageComponent,
		GameState,
		
		// number of components
		_LastCmptId_
	};

	enum GrpId : GroupId {
		_grp_Star,
		_grp_Ghost,
		_grp_Food,
		
		// number of groups
		_LastGrpId_
	};

	enum HdlrId : HandlerId 
	{
		_hdlr_PacManEntity,
		_hdlr_GameStateEntity,
	
		// number of handlers
		_LastHdlrId_
	};

	enum SysId : SystemId 
	{
		_sys_GameCtrl,
		_sys_PacMan,
		_sys_Ghosts,
		_sys_Food,
		_sys_Render,
		_sys_Collisions,
		_sys_ScoreMngr,
		_sys_Sound,

		// number of systems
		_LastSysId_
	};

	constexpr std::size_t maxComponents = _LastCmptId_;
	constexpr std::size_t maxGroups = _LastGrpId_;
	constexpr std::size_t maxHandlers = _LastHdlrId_;
	constexpr std::size_t maxSystems = _LastSysId_;

#define GETCMP2_(id,type)	GETCMP3(entity_, id,type)
#define GETCMP1_(type)		GETCMP3(entity_, ECS::type,type)

#define GETCMP2(e,type)		GETCMP3(e, ECS::type,type)
#define GETCMP3(e,id,type)	e->getComponent<type>(id)
}

#endif // !__ECS_H__