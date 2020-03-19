#ifndef __ECS_H__
#define __ECS_H__

#include <ctime>
#include "MPL.h"

// Identificadores de componentes (corresponden a componentes con los mismos nombres)
struct Transform;
struct ImageComponent;
struct AsteroidLifeTime;
struct Score;
struct GameState;
struct Health;
struct Rotation;

using ComponentsList = MPL::TypeList<Transform, ImageComponent, Score, AsteroidLifeTime, GameState, Health, Rotation>;

// Identificadores de grupos
struct _grp_Bullet;
struct _grp_Asteroid;

using GroupsList = MPL::TypeList<_grp_Asteroid, _grp_Bullet>;

// Identificadores de handlers
struct _hdlr_Fighter;
struct _hdlr_GameState;

using HandlersList = MPL::TypeList<_hdlr_Fighter, _hdlr_GameState>;

// Identificadores de sistemas
class RenderSystem;
class GameCtrlSystem;
class CollisionSystem;
class FighterSystem;
class AsteroidsSystem;
class AsteroidsSystem;
class BulletsSystem;
class FighterGunSystem;

using SystemsList = MPL::TypeList<RenderSystem, GameCtrlSystem, CollisionSystem, FighterSystem, AsteroidsSystem, BulletsSystem, FighterGunSystem>;

constexpr std::size_t maxComponents = ComponentsList::size;
constexpr std::size_t maxGroups = GroupsList::size;
constexpr std::size_t maxHandlers = HandlersList::size;
constexpr std::size_t maxSystems = SystemsList::size;

#endif // !__ECS_H__