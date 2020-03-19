#ifndef __OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__

#include "Singleton.h"
#include "MemoryPool.h"

// Clase para gestionar la creaci�n y destrucci�n de objetos de tipo T.
// Se implementa utilizando el patr�n de dise�o Singleton, lo que nos
// permite controlar cu�ndo se realiza la inicializaci�n del pool de memoria.
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

	// Llama al m�todo de construcci�n de la instancia �nica
	template<typename ...Targs>
	inline static T* construct(Targs&&...args) 
	{
		return ObjectFactory<T>::instance()->construct_(std::forward<Targs>(args)...);
	}

	// Llama al m�todo de destrucci�n de la instancia �nica
	inline static void destroy(T* p) 
	{
		ObjectFactory<T>::instance()->destroy_(p);
	}

	// Llama al m�todo de construcci�n del pool de memoria
	// Devuelve el objeto de tipo T construido
	template<typename ...Targs>
	inline T* construct_(Targs&&...args) 
	{
		memPool_.construct(std::forward<Targs>(args)...);
	}

	// Llama al m�todo de destrucci�n del pool de memoria
	inline void destroy_(T* p) 
	{
		memPool_.destroy(p);
	}

private:
	// Constructora por defecto
	// Crea un pool de memoria con un tama�o de 10
	ObjectFactory() :
		ObjectFactory(10) 
	{
	}

	// Constructora con par�metros
	// Crea un pool de memoria con un tama�o de n
	ObjectFactory(std::size_t n) :
		memPool_(n) 
	{
	}
};

#endif // !__OBJECT_FACTORY_H__