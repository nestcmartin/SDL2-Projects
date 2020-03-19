#ifndef __OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__

#include "Singleton.h"
#include "MemoryPool.h"

// Clase para gestionar la creación y destrucción de objetos de tipo T.
// Se implementa utilizando el patrón de diseño Singleton, lo que nos
// permite controlar cuándo se realiza la inicialización del pool de memoria.
template<typename T>
class ObjectFactory : public Singleton<ObjectFactory<T>>
{
	friend Singleton<ObjectFactory<T>>;

private:
	MemoryPool<T> memPool_;	// Pool de memoria para asignar a los objetos de tipo T

public:
	virtual ~ObjectFactory()
	{
	}

	// Llama al método de construcción de la instancia única
	template<typename ...Targs>
	inline static T* construct(Targs&&...args) 
	{
		return ObjectFactory<T>::instance()->construct_(std::forward<Targs>(args)...);
	}

	// Llama al método de destrucción de la instancia única
	inline static void destroy(T* p) 
	{
		ObjectFactory<T>::instance()->destroy_(p);
	}

	// Llama al método de construcción del pool de memoria
	// Devuelve el objeto de tipo T construido
	template<typename ...Targs>
	inline T* construct_(Targs&&...args) 
	{
		memPool_.construct(std::forward<Targs>(args)...);
	}

	// Llama al método de destrucción del pool de memoria
	inline void destroy_(T* p) 
	{
		memPool_.destroy(p);
	}

private:
	// Constructora por defecto
	// Crea un pool de memoria con un tamaño de 10
	ObjectFactory() :
		ObjectFactory(10) 
	{
	}

	// Constructora con parámetros
	// Crea un pool de memoria con un tamaño de n
	ObjectFactory(std::size_t n) :
		memPool_(n) 
	{
	}
};

#endif // !__OBJECT_FACTORY_H__