#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <list>

#include "Entity.h"
#include "DefaultFactory.h"
#include "ObjectFactory.h"

#include "System.h"

#include "ECS.h"
#include "SDLGame.h"
#include "Messages.h"

// Clase que gestiona las entidades y su comunicación
class EntityManager
{
	using EventType = std::function<void()>;												// Función sin argumentos que no devuelve nada (actúa como Lambda)
	using EntityPtr = std::unique_ptr<Entity, std::function<void(Entity*)>>;				// Unique pointer a un par Entidad-Función de Entidad
	using MessagePtr = std::unique_ptr<MSG::Message, std::function<void(MSG::Message*)>>;		// Unique pointer a un par Mensaje-Función de Mensaje

private:
	SDLGame* game_;		// Puntero al juego al que pertenecen las entidades

	std::list<EventType> events_;		// Lista de eventos
	std::list<MessagePtr>* messages_;	// Lista de mensajes

	std::vector<EntityPtr> entities_;								// Lista de entidades activas
	std::array<Entity*, ECS::maxHandlers> handlers_;				// Lista de manejadores
	std::array<std::unique_ptr<System>, ECS::maxSystems> systems_;	// Lista de sistemas
	std::array<std::vector<Entity*>, ECS::maxGroups> entityGroups_;	// Lista de grupos de entidades


public:
	// Constructora
	EntityManager(SDLGame* game) :
		game_(game)
	{
		messages_ = new std::list<MessagePtr>();
	}

	// Destructora
	virtual ~EntityManager()
	{
		delete messages_;
	}

	// Elimina las entidades no activas y modifica los grupos
	void refresh();


	// GESTION DE ENTIDADES -----------------------------------------------------------

	// Devuelve la lista de entidades activas
	const std::vector<EntityPtr>& getEntities()
	{
		return entities_;
	}

	// Añade una entidad
	template<typename FT = DefaultFactory<Entity>, typename ...Targs>
	inline Entity* addEntity(Targs&&...args)
	{
		// Utilizamos la factoría de tipo FT para crear la entidad
		Entity* e = FT::construct(std::forward<Targs>(args)...);
		if (e != nullptr)
		{
			e->setEntityManager(this);
			e->resetGroups();

			// Añadimos a la cola de eventos una función anónima (Lambda expression) 
			// que se encarga de añadir la entidad 'e' a lista de entidades activas
			events_.push_back([this, e]() {	// La lista de capturas de la expresión incluye this por tratarse de una función miembro anónima
				entities_.emplace_back(e,	// Utilizamos emplace_back para crear el EntityPtr in-place y colocarlo al final de la lista
					[](Entity* p) {			// El EntityPtr necesita como segundo argumento del template una función que toma un puntero a Entity como parámetro
						FT::destroy(p);		// Como las funciones de las factorías son estáticas la lista de captura de la expresión no necesita this
					});
				});
		}
		return e;
	}


	// GESTION DE GRUPOS ---------------------------------------------------------------

	// Devuelve un grupo de entidades
	const std::vector<Entity*>& getGroupEntities(ECS::GrpIdType grpId)
	{
		return entityGroups_[grpId];
	}

	// Añade una entidad a un grupo
	inline void addToGroup(std::size_t grpId, Entity* e)
	{
		events_.push_back([this, grpId, e]() {
			entityGroups_[grpId].push_back(e);
			});
	}


	// GESTION DE MANEJADORES ----------------------------------------------------------

	// Establece un manejador para una entidad
	inline void setHandler(ECS::HdlrIdType id, Entity* e) 
	{
		handlers_[id] = e;
	}

	// Devuelve la entidad asociada a un manejador
	inline Entity* getHandler(ECS::HdlrIdType id)
	{
		return handlers_[id];
	}


	// GESTION DE SISTEMAS -------------------------------------------------------------

	// Añade un sistema
	template<typename T, typename ...Targs>
	T* addSystem(Targs&&... args)
	{
		T* s = new T(std::forward<Targs>(args)...);
		systems_[s->getId()] = std::unique_ptr<T>(s);
		s->setGame(game_);
		s->setMngr(this);
		s->init();
		return s;
	}

	// Devuelve el sistema de tipo T
	template<typename T>
	T* getSystem(ECS::SysIdType id) 
	{
		return static_cast<T*>(systems_[id].get());
	}


	// GESTION DE MENSAJES -----------------------------------------------------------

	// Envia un mensaje
	template<typename T, typename FT = ObjectFactory<T>, typename ...Ts>
	void send(Ts&&...args)
	{
		MSG::Message* msg = FT::construct(std::forward<Ts>(args)...);
		msg->senderClientId = game_->getNetworking()->getClientId();

		MessagePtr uPtr(msg, [](MSG::Message* p) {
			FT::destroy(static_cast<T*>(p));
			});

		messages_->push_back(std::move(uPtr));
	}

	// Reenvia un mensaje
	template<typename T, typename FT = ObjectFactory<T>, typename ...Ts>
	void forwardMsg(uint32_t clientId, Ts&&...args)
	{
		MSG::Message* msg = FT::construct(std::forward<Ts>(args)...);
		msg->senderClientId = clientId;

		MessagePtr uPtr(msg, [](MSG::Message* p) {
			FT::destroy(static_cast<T*>(p));
			});

		messages_->push_back(std::move(uPtr));
	}

	// Elimina toda la cola de mensajes
	void flushMessages()
	{
		while (!messages_->empty())
		{
			MessagePtr msg = std::move(messages_->front());
			for (auto& s : systems_)
			{
				if (s != nullptr) s->receive(*msg);
			}
			messages_->pop_front();
		}

	}

	// Consulta el id del cliente
	inline uint32_t getClientId()
	{
		return game_->getNetworking()->getClientId();
	}

};

#endif // !__ENTITY_MANAGER_H__