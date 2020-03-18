#ifndef __DEFAULT_FACTORY_H__
#define __DEFAULT_FACTORY_H__

#include <utility>

// Clase para gestionar la creación y destrucción de objetos de tipo T.
// Se implementa de un modo básico, haciendo uso de los operadores new y delete.
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

	// Devuelve un objeto de tipo T
	template<typename ...Targs>
	inline static T* construct(Targs&& ...args)
	{
		return new T(std::forward<Targs>(args)...);
	}

	// Destruye el objeto de tipo T
	inline static void destroy(T* p)
	{
		delete p;
	}
};

#endif // !__DEFAULT_FACTORY_H__