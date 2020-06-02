#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include <cassert>
#include <vector>
#include <list>

template<typename T>
class ObjectPool
{
private:
	std::size_t size_;
	T* objects_;
	std::vector<T*> objectPtrs_;
	std::list<T*> freeObjects_;

public:
	ObjectPool(std::size_t size)
	{
		size_ = size;
		objects_ = new T[size_];
		for (auto i(0u); i < size_; i++)
		{
			objectPtrs_.push_back(&objects_[i]);
			freeObjects_.push_back(&objects_[i]);
		}
	}

	virtual ~ObjectPool()
	{
		delete[] objects_;
	}

	const std::vector<T*>& getPool() { return objectPtrs_; }

	T* getObject()
	{
		if (!freeObjects_.empty())
		{
			T* o = freeObjects_.front();
			freeObjects_.pop_front();
			return o;
		}
		else
		{
			return nullptr;
		}
	}

	void releaseObject(T* p) 
	{
		std::size_t idx = p - objects_;
		assert(idx >= 0 && idx < size_);
		freeObjects_.push_back(p);
	}
};

#endif // !__OBJECT_POOL_H__