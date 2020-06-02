#ifndef __MEMORY_POOL_H__
#define __MEMORY_POOL_H__

#include "ObjectFactory.h"

#include "Singleton.h"

template<typename T>
class MemoryPool : public Singleton<MemoryPool<T>>
{
	friend Singleton<MemoryPool<T>>;

private:
	ObjectFactory<T> pool_;

public:
	virtual ~MemoryPool() 
	{
	}

	template<typename ...Targs>
	inline static T* construct(Targs&&...args) 
	{
		return MemoryPool<T>::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(T* p) 
	{
		MemoryPool<T>::instance()->destroy_(p);
	}

	template<typename ...Targs>
	inline T* construct_(Targs&&...args) 
	{
		return pool_.construct(std::forward<Targs>(args)...);
	}

	inline void destroy_(T* p) 
	{
		pool_.destroy(p);
	}

private:
	MemoryPool() :
		MemoryPool(10) 
	{
	}

	MemoryPool(std::size_t n) :
		pool_(n) 
	{
	}
};

#endif // !__MEMORY_POOL_H__