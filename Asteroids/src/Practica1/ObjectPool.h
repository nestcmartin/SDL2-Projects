#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include <array>
#include <vector>
#include <functional>

template<typename T, int SIZE>
class ObjectPool 
{
public:
	ObjectPool(std::function<bool(T*)> f)
	{
		inUseF_ = f;
		for (auto& b : objs_)
		{
			objsPtrs_.push_back(&b);
		}
	}

	~ObjectPool()
	{
	}

	T* getObj()
	{
		for (auto& o : objs_)
		{
			if (!inUseF_(&o)) return &o;
		}
		return nullptr;
	}

	const std::vector<T*>& getPool()
	{
		return objsPtrs_;
	}

private:
	std::function<bool(T*)> inUseF_;
	std::array<T, SIZE> objs_;
	std::vector<T*> objsPtrs_;
};

#endif // !__OBJECT_POOL_H__