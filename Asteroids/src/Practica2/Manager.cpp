#include "EntityManager.h"

#include <algorithm>

void EntityManager::refresh() 
{
	// Ejecuta todos los eventos
	// Se accede al primer evento, se ejecuta, y se saca de la cola
	while (!events_.empty()) 
	{
		auto &event = events_.front();
		event();
		events_.pop_front();
	}

	// Actualiza todos los grupos de entidades
	// Si una entidad en un grupo no está activa o no tiene grupo, se elimina del grupo
	for (auto i(0u); i < maxGroups; i++) 
	{
		auto &grp = entityGroups_[i];
		grp.erase(std::remove_if(grp.begin(), grp.end(), [i](Entity *e) { return !e->isActive() || !e->hasGroup(i); }), grp.end());
	}

	// Actualiza la lista de entidades activas
	// Si una entidad no está activa se elimina de la lista de entidades activas
	entities_.erase(std::remove_if(entities_.begin(), entities_.end(), [](const EntityPtr &e) { return !e->isActive(); }), entities_.end());
}