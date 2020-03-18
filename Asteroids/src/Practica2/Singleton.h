#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <memory>

/*
 * Clase para implementar el patron de diseño Singleton.
 * La clase debe heredar públicamente de Singleton (class A : public Singleton<A>).
 * La clase debe poder acceder al Singleton (friend Singleton<A>).
 * La clase debe mantener todas las constructoras como privadas.
 * La clase debe mantener pública y virtual la destructora.
 */
template<typename T>
class Singleton 
{
private:
	static std::unique_ptr<T> instance_;

protected:
	Singleton() 
	{
	}

public:
	virtual ~Singleton() 
	{
	}

	// Inicializa el Singleton con parametros.
	// Se recomienda hacer esto al inicio del programa.
	template<typename ...Targs>
	inline static T* init(Targs&&...args) 
	{
		assert(instance_.get() == nullptr);
		instance_.reset(new T(std::forward<Targs>(args)...));
		return instance_.get();
	}

	// Restaura la instancia única del Singleton.
	// A veces, cuando los Singleton tienen dependcias,
	// es necesario cerrarlos en un orden específico.
	inline static void close() 
	{
		instance_.reset();
	}

	// Accede a la instancia única dell Singleton.
	inline static T* instance() 
	{
		if (instance_.get() == nullptr) 
		{
			instance_.reset(init());
		}
		return instance_.get();
	}
};

template<typename T>
std::unique_ptr<T> Singleton<T>::instance_;

#endif // !__SINGLETON_H__