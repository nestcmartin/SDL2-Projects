#include "ObjectPool.h"

template<typename T, int SIZE>
ObjectPool<T, SIZE>::ObjectPool(std::function<bool(T*)> f)
{
	inUseF_ = f;
	for (auto& b : objs_) 
	{
		objsPtrs_.push_back(&b);
	}
}

template<typename T, int SIZE>
inline ObjectPool<T, SIZE>::~ObjectPool()
{
}

template<typename T, int SIZE>
T* ObjectPool<T, SIZE>::getObj()
{
	for (auto& o : objs_) 
	{
		if (!inUseF_(&o)) return &o;
	}
	return nullptr;
}
