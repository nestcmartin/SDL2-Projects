#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include <array>
#include <vector>
#include <functional>

template<typename T, int SIZE>
class ObjectPool 
{
public:
	ObjectPool(std::function<bool(T*)> f);
	virtual ~ObjectPool();

	const std::vector<T*>& getPool() { return objsPtrs_; }

	T* getObj();

private:
	std::function<bool(T*)> inUseF_;
	std::array<T, SIZE> objs_;
	std::vector<T*> objsPtrs_;
};

#endif // !__OBJECT_POOL_H__