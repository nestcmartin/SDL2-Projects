#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <SDL.h>

#include "ECS.h"
#include "SDLGame.h"

class Entity;

class Component 
{
protected:
	SDLGame* game_;			// Puntero al SDLGame al que pertenece el componente
	Entity* entity_;		// Puntero a la Entidad a la que pertenece el componente
	ECS::ComponentId id_;	// Identificador unívoco del componente

public:
	Component(ECS::ComponentId id);
	virtual ~Component();

	inline ECS::ComponentId getId() const { return id_; }
	inline void setId(ECS::ComponentId id) { id_ = id; }
	inline void setGame(SDLGame* game) { game_ = game; }
	inline void setEntity(Entity* entity) { entity_ = entity; }

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
};

#endif // !__COMPONENT_H__