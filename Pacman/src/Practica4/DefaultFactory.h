#ifndef __DEFAULT_FACTORY_H__
#define __DEFAULT_FACTORY_H__

#include <utility>

template<typename T>
class DefaultFactory 
{
public:
	DefaultFactory() 
	{
	}
	
	virtual ~DefaultFactory() 
	{
	}

	template<typename ...Targs>
	inline static T* construct(Targs&& ...args) 
	{
		return new T(std::forward<Targs>(args)...);
	}

	inline static void destroy(T* p) 
	{
		delete p;
	}
};

#endif // !__DEFAULT_FACTORY_H__