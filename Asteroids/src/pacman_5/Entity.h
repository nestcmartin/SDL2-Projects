#pragma once

#include <iostream>
#include <array>
#include <bitset>
#include <functional>

#include "Component.h"
#include "DefFactory.h"
#include "SDLGame.h"
#include "ecs.h"

// We don't include the EntityManager class to avoid circular dependeincies
class Manager;

class Entity {

	// defining a type just for brevity
	using uptr_cmp = std::unique_ptr<Component,std::function<void(Component*)>>;

public:
	Entity() :
			game_(SDLGame::instance()), //
			mngr_(nullptr), //
			active_(true) {
	}

	virtual ~Entity() {
	}

	inline Manager* getEntityMngr() const {
		return mngr_;
	}

	inline void setEntityMngr(Manager *mngr) {
		mngr_ = mngr;
	}

	inline bool isActive() const {
		return active_;
	}

	inline void setActive(bool active) {
		active_ = active;
	}

	template<typename T>
	inline T* getComponent() {
		constexpr std::size_t id = mpl::IndexOf<T,ComponentsList>();
		return static_cast<T*>(cmpArray_[id].get());
	}

	template<typename T>
	inline bool hasComponent() {
		constexpr std::size_t id = mpl::IndexOf<T,ComponentsList>();
		return cmpArray_[id] != nullptr;
	}

	template<typename T, typename FT = DefFactory<T>, typename ... Targs>
	inline T* addComponent(Targs &&...args) {

		// create the actual component ...
		T *c = FT::construct(std::forward<Targs>(args)...);
		uptr_cmp uPtr(c, [](Component *p) {
			FT::destroy(static_cast<T*>(p));
		});

		// store it in the components array
		constexpr std::size_t id = mpl::IndexOf<T,ComponentsList>();
		cmpArray_[id] = std::move(uPtr);

		return c;
	}

	template<typename T>
	inline void removeComponent() {
		constexpr std::size_t id = mpl::IndexOf<T,ComponentsList>();
		 cmpArray_[id] = nullptr;
	}

	template<typename TG>
	void addToGroup() {
		constexpr std::size_t grpId = mpl::IndexOf<TG,GroupsList>();
		addToGroup(grpId);
	}

	// defined in CPP since it access the manager
	void addToGroup(std::size_t id);

	template<typename TG>
	inline void removeFromGroup() {
		constexpr std::size_t grpId = mpl::IndexOf<TG,GroupsList>();
		groups_[grpId] = false;
	}

	inline void resetGroups() {
		groups_.reset();
	}

	template<typename TG>
	inline bool hasGroup() {
		constexpr std::size_t grpId = mpl::IndexOf<TG,GroupsList>();
		return hasGroup(grpId);
	}

	inline bool hasGroup(std::size_t grpId) {
		return groups_[grpId];
	}
private:
	SDLGame *game_;
	Manager *mngr_;

	std::array<uptr_cmp, maxComponents> cmpArray_ = { };
	std::bitset<maxGroups> groups_;


	bool active_;
};

