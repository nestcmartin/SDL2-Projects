#pragma once

#include <ctime>
#include "mpl.h"

// ** Components
//
// They must match the names of your components.
//
struct Transform;
struct ImageComponent;
struct Rotation;
struct Score;
struct LifeTime;

using ComponentsList =
mpl::TypeList<Transform,ImageComponent,Rotation,Score,LifeTime>;

// ** Groups
//
// start them with _grp_ to avoid conflicts (or make a name space)
//
struct _grp_Star;

using GroupsList =
mpl::TypeList<_grp_Star>;

// ** handlers
//
// start them with _grp_ to avoid conflicts (or make a name space)
//
struct _hdlr_PacMan;
struct _hdlr_GameState;

using HandlersList =
mpl::TypeList<_hdlr_PacMan,_hdlr_GameState>;

// ** Systems
//
// they must match the name of the systems classes

class CollisionSystem;
class GameCtrlSystem;
class PacManSystem;
class StarsSystem;
class RenderSystem;

using SystemsList =
mpl::TypeList<CollisionSystem,GameCtrlSystem,PacManSystem,StarsSystem,RenderSystem>;

constexpr std::size_t maxComponents = ComponentsList::size;
constexpr std::size_t maxGroups = GroupsList::size;
constexpr std::size_t maxHandlers = HandlersList::size;
constexpr std::size_t maxSystems = SystemsList::size;


// These macros are obselete ... you can ucomment them if needed,
// but better use getComponent directly

/*
// these two should be used to get a component via the field
// entity_
#define GETCMP2_(id,type)  GETCMP2(entity_,type)
#define GETCMP1_(type)     GETCMP2(entity_,type)

// these two should be used to get a component via an
// entity e provided as a parameter
#define GETCMP2(e,type) e->getComponent<type>()
#define GETCMP3(e,id,type) e->getComponent<type>()
*/

