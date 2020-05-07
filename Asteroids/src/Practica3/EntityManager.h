#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <list>

#include "Entity.h"
#include "DefaultFactory.h"

#include "System.h"

#include "ECS.h"
#include "SDLGame.h"

// Clase que gestiona las entidades y su comunicaci�n
class EntityManager 
{
	using EventType = std::function<void()>;									// Funci�n sin argumentos que no devuelve nada (act�a como Lambda)
	using EntityPtr = std::unique_ptr<Entity, std::function<void(Entity*)>>;	// Unique pointer a un par Entidad-Funci�n de Entidad

private:
	SDLGame* game_;												// Puntero al juego al que pertenecen las entidades
	std::list<EventType> events_;								// Lista de eventos
	std::vector<EntityPtr> entities_;							// Lista de entidades activas
	std::array<Entity*, maxHandlers> handlers_;					// Lista de manejadores
	std::array<std::unique_ptr<System>, maxSystems> systems_;	// Lista de sistemas
	std::array<std::vector<Entity*>, maxGroups> entityGroups_;	// Lista de grupos de entidades


public:
	// Constructora
	EntityManager(SDLGame* game) :
		game_(game) 
	{
	}

	// Destructora
	virtual ~EntityManager() 
	{
	}

	// Elimina las entidades no activas y modifica los grupos
	void refresh();

	// Devuelve el grupo de tipo TG
	template<typename TG>
	const std::vector<Entity*>& getGroupEntities() 
	{
		constexpr std::size_t grpId = MPL::IndexOf<TG, GroupsList>();
		return entityGroups_[grpId];
	}

	// Devuelve la lista de entidades activas
	const std::vector<EntityPtr>& getEntities() 
	{
		return entities_; 
	}

	// A�ade una entidad
	template<typename FT = DefaultFactory<Entity>, typename ...Targs>
	inline Entity* addEntity(Targs&&...args) 
	{
		// Utilizamos la factor�a de tipo FT para crear la entidad
		Entity* e = FT::construct(std::forward<Targs>(args)...);
		if (e != nullptr) 
		{
			e->setEntityManager(this);
			e->resetGroups();

			// A�adimos a la cola de eventos una funci�n an�nima (Lambda expression) 
			// que se encarga de a�adir la entidad 'e' a lista de entidades activas
			events_.push_back([this, e]() {	// La lista de capturas de la expresi�n incluye this por tratarse de una funci�n miembro an�nima
				entities_.emplace_back(e,	// Utilizamos emplace_back para crear el EntityPtr in-place y colocarlo al final de la lista
					[](Entity* p) {			// El EntityPtr necesita como segundo argumento del template una funci�n que toma un puntero a Entity como par�metro
					FT::destroy(p);			// Como las funciones de las factor�as son est�ticas la lista de captura de la expresi�n no necesita this
					});
				});
		}
		return e;
	}

	// A�ade una entidad e a un grupo con identificador grpId
	inline void addToGroup(std::size_t grpId, Entity* e) 
	{
		events_.push_back([this, grpId, e]() {
			entityGroups_[grpId].push_back(e);
			});
	}


	// Establece un manejador de tipo TH para la entidad e
	template<typename TH>
	inline void setHandler(Entity* e) 
	{
		constexpr std::size_t id = MPL::IndexOf<TH, HandlersList>();
		handlers_[id] = e;
	}

	// Devuelve el manejador de tipo TH
	template<typename TH>
	inline Entity* getHandler() 
	{
		constexpr std::size_t id = MPL::IndexOf<TH, HandlersList>();
		return handlers_[id];
	}

	// A�ade un sistema
	template<typename T, typename ...Targs>
	T* addSystem(Targs&&... args) 
	{
		constexpr std::size_t sysId = MPL::IndexOf<T, SystemsList>();
		T* s = new T(std::forward<Targs>(args)...);
		systems_[sysId] = std::unique_ptr<T>(s);
		s->setGame(game_);
		s->setMngr(this);
		s->init();
		return s;
	}

	// Devuelve el sistema de tipo T
	template<typename T>
	T* getSystem() 
	{
		constexpr std::size_t sysId = MPL::IndexOf<T, SystemsList>();
		return static_cast<T*>(systems_[sysId].get());
	}
};

#endif // !__ENTITY_MANAGER_H__