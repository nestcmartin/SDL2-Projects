#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <iostream>
#include <array>
#include <bitset>
#include <functional>

#include "DefaultFactory.h"

#include "Component.h"

#include "ECS.h"
#include "SDLGame.h"

class EntityManager;

// Clase que define el comportamiento de las entidades
class Entity
{
	using uptr_cmp = std::unique_ptr<Component, std::function<void(Component*)>>;

private:
	bool active_;											// Indica si la entidad está o no activa
	SDLGame* game_;											// Puntero al juego al que pertenece la entidad
	EntityManager* entityManager_;								// Puntero al gestor de entidades al que pertenece la entidad
	std::bitset<maxGroups> groups_;							// Máscara de bits que indica los grupos a los que pertenece la entidad
	std::array<uptr_cmp, maxComponents> components_ = {};	// Lista de componentes de la entidad

public:
	// Constructora
	Entity() :
		game_(SDLGame::instance()),
		entityManager_(nullptr),
		active_(true)
	{
	}

	// Destructora
	virtual ~Entity()
	{
	}

	// Getters y Setters
	inline EntityManager* getEntityManager() const { return entityManager_; }
	inline void setEntityManager(EntityManager* mngr) { entityManager_ = mngr; }
	inline bool isActive() const { return active_; }
	inline void setActive(bool active) { active_ = active; }

	// Devuelve el componente de tipo T
	template<typename T>
	inline T* getComponent()
	{
		constexpr std::size_t id = MPL::IndexOf<T, ComponentsList>();
		return static_cast<T*>(components_[id].get());
	}

	// Comprueba si la entidad posee un componente de tipo T
	template<typename T>
	inline bool hasComponent()
	{
		constexpr std::size_t id = MPL::IndexOf<T, ComponentsList>();
		return components_[id] != nullptr;
	}

	// Añade un componente de tipo T y lo devuelve
	// Si no se especifica una factoría, el componente se crea con DefaultFactory<T>
	// Si la entidad ya poseía un componente del mismo tipo se sustituye por el nuevo
	template<typename T, typename FT = DefaultFactory<T>, typename ... Targs>
	inline T* addComponent(Targs&&...args)
	{
		T* c = FT::construct(std::forward<Targs>(args)...);
		uptr_cmp uPtr(c, [](Component* p) {
			FT::destroy(static_cast<T*>(p));
			});

		constexpr std::size_t id = MPL::IndexOf<T, ComponentsList>();
		components_[id] = std::move(uPtr);

		return c;
	}

	// Elimina el componente de tipo T
	template<typename T>
	inline void removeComponent() 
	{
		constexpr std::size_t id = MPL::IndexOf<T, ComponentsList>();
		components_[id] = nullptr;
	}

	// Añade la entidad al grupo de tipo TG
	template<typename TG>
	void addToGroup() 
	{
		constexpr std::size_t grpId = MPL::IndexOf<TG, GroupsList>();
		addToGroup(grpId);
	}

	// Añade la entidad al grupo con identificador id
	void addToGroup(std::size_t id);

	// Elimina la entidad del grupo de tipo TG
	template<typename TG>
	inline void removeFromGroup() 
	{
		constexpr std::size_t grpId = MPL::IndexOf<TG, GroupsList>();
		groups_[grpId] = false;
	}

	// Elimina la entidad de todos los grupos
	inline void resetGroups() 
	{
		groups_.reset();
	}

	// Comprueba si la entidad pertenece al grupo de tipo TG
	template<typename TG>
	inline bool hasGroup() 
	{
		constexpr std::size_t grpId = MPL::IndexOf<TG, GroupsList>();
		return hasGroup(grpId);
	}

	// Comprueba si la entidad pertenece al grupo con identificador ID
	inline bool hasGroup(std::size_t grpId) 
	{
		return groups_[grpId];
	}
};

#endif // !__ENTITY_H__