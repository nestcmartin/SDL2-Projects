#ifndef __ECS_H__
#define __ECS_H__

#include <ctime>

namespace ECS 
{
	using CmpIdType = std::size_t;
	using GrpIdType = std::size_t;
	using HdlrIdType = std::size_t;
	using SysIdType = std::size_t;

	// Identificadores de componentes
	enum ComponentId : CmpIdType 
	{
		Transform = 0,
		Image,
		GameState,
		CtrlKeys,
		FighterInfo,

		// YOU SHALL NOT PASS
		_LastCmptId_
	};

	// Identificadores de grupos
	enum GroupId : GrpIdType 
	{
		_grp_Fighters,
		_grp_Bullets,

		// YOU SHALL NOT PASS
		_LastGrpId_
	};

	// Identificadores de handlers
	enum HandlerId : HdlrIdType 
	{
		_hdlr_Fighter0,
		_hdlr_Fighter1,

		// YOU SHALL NOT PASS
		_LastHdlrId_
	};

	// Identificadores de sistemas
	enum SystemId : SysIdType 
	{
		_sys_GameCtrl,
		_sys_Fighters,
		_sys_Bullets,
		_sys_Collision,
		_sys_Render,
		_sys_NetWorking,

		// YOU SHALL NOT PASS
		_LastSysId_
	};

	constexpr std::size_t maxComponents = _LastCmptId_;
	constexpr std::size_t maxGroups = _LastGrpId_;
	constexpr std::size_t maxHandlers = _LastHdlrId_;
	constexpr std::size_t maxSystems = _LastSysId_;

// Se devuelve un componente a partir del atributo entity_
#define GETCMP2_(id, type)   GETCMP3(entity_, id, type)
#define GETCMP1_(type)       GETCMP3(entity_, ECS::type, type)

// Se devuelve un componente a partir del parámetro e
#define GETCMP2(e, type)     GETCMP3(e, ECS::type, type)
#define GETCMP3(e, id, type) e->getComponent<type>(id)

}

#endif // !__ECS_H__