#ifndef __ECS_H__
#define __ECS_H__

#include <ctime>
#include "MPL.h"

// COMPONENTS
struct Transform;
struct ImageComponent;
struct Rotation;
struct Score;
struct LifeTime;

using ComponentsList = MPL::TypeList<Transform, ImageComponent, Rotation, Score, LifeTime>;

// GROUPS
struct _grp_Star;

using GroupsList = MPL::TypeList<_grp_Star>;

// HANDLERS
struct _hdlr_PacMan;
struct _hdlr_GameState;

using HandlersList = MPL::TypeList<_hdlr_PacMan, _hdlr_GameState>;

// SYSTEMS
class CollisionSystem;
class GameCtrlSystem;
class PacManSystem;
class StarsSystem;
class RenderSystem;

using SystemsList = MPL::TypeList<CollisionSystem, GameCtrlSystem, PacManSystem, StarsSystem, RenderSystem>;

constexpr std::size_t maxComponents = ComponentsList::size;
constexpr std::size_t maxGroups = GroupsList::size;
constexpr std::size_t maxHandlers = HandlersList::size;
constexpr std::size_t maxSystems = SystemsList::size;

#endif // !__ECS_H__