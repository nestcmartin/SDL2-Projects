#ifndef __OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__

#include <cassert>
#include <cstdlib>
#include <memory>
#include <new>

template<typename T, typename AllocType = std::allocator<T>>
class ObjectFactory 
{
private:
	std::size_t size_;
	T* memory_;
	bool* used_;
	AllocType allocator_;

public:
	ObjectFactory(int n) 
	{
		size_ = n;
		//mem_ = static_cast<T*>(_VSTD::__libcpp_allocate(size_ * sizeof(T), _LIBCPP_ALIGNOF(T)));
		memory_ = allocator_.allocate(size_);
		used_ = new bool[size_]();
	}

	virtual ~ObjectFactory() 
	{
        //_VSTD::__libcpp_deallocate((void*)mem_, size_ * sizeof(T), _LIBCPP_ALIGNOF(T));
		allocator_.deallocate(memory_,size_);
	}

	template<typename... Targs>
	T* construct(Targs&& ...args) 
	{
		for(int i=0; i<size_; i++) 
		{
			if ( !used_[i] ) {
				used_[i] = true;
				//::new(&mem_[i]) T(std::forward<Targs>(args)...);
				allocator_.construct(&memory_[i],std::forward<Targs>(args)...);
				return &memory_[i];
			}
		}
		return nullptr;
	}

	void destroy(T* p) 
	{
		int idx = p-memory_;
		assert(idx >=0 && idx < size_);
		used_[idx] = false;
		//p->~T();
		allocator_.destroy(p);
	}
};

#endif // !__OBJECT_FACTORY_H__