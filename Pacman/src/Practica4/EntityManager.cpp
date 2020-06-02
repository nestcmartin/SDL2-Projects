#include "EntityManager.h"

#include <algorithm>

void EntityManager::refresh()
{
	// execute all events
	while (!events_.empty())
	{
		auto& event = events_.front();
		event();
		events_.pop_front();
	}

	// update groups
	for (auto i(0u); i < ECS::maxGroups; i++)
	{
		auto& grp = groups_[i];
		grp.erase(
			std::remove_if(
				grp.begin(),
				grp.end(),
				[i](Entity* e) {
					return !e->isActive() || !e->hasGroup(i);
				}),
			grp.end());
	}

	// update the list of enteties
	entities_.erase(
		std::remove_if(
			entities_.begin(),
			entities_.end(),
			[](const EntityPtr& e) {
				return !e->isActive();
			}),
		entities_.end());
}

