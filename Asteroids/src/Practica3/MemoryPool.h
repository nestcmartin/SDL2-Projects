#ifndef __MEMORY_POOL_H__
#define __MEMORY_POOL_H__

#include <cassert>
#include <cstdlib>
#include <memory>
#include <new>

// Clase para gestionar la asignación de memoria para objetos de tipo T.
// Utiliza std::allocator para reservar y liberar la memoria, 
// así como para construir y destruir los objetos de tipo T.
template<typename T, typename AllocType = std::allocator<T>>
class MemoryPool
{
private:
	T* mem_;			// Pool de memoria de objetos de tipo T
	bool* used_;		// Indica qué bloques del pool de memoria están ocupados
	AllocType alloc_;	// Allocator utilizado para reservar, construir, destruir y liberar
	std::size_t size_;	// Numero de elementos de tipo T que puede contener el pool de memoria

public:
	// Construtora
	// Reserva memoria para n objetos de tipo T
	MemoryPool(int n)
	{
		size_ = n;
		mem_ = alloc_.allocate(size_);
		used_ = new bool[size_]();
	}

	// Destructora
	// Libera toda la memoria reservada del pool
	virtual ~MemoryPool() 
	{
		alloc_.deallocate(mem_, size_);
		delete[] used_;
	}

	// Asigna un espacio de memoria a un objeto de tipo T
	// Marca como no disponible dicho espacio de memoria
	// Llama a la constructora del objeto de tipo T
	// Devuelve un puntero al objeto de tipo T
	template<typename... Targs>
	T* construct(Targs&& ...args) 
	{
		for (int i = 0; i < size_; i++) 
		{
			if (!used_[i]) 
			{
				used_[i] = true;
				alloc_.construct(&mem_[i], std::forward<Targs>(args)...);
				return &mem_[i];
			}
		}
		return nullptr;
	}

	// Marca como disponible el espacio de memoria del objeto de tipo T
	// Llama a la destructora del objeto de tipo T
	void destroy(T* p) 
	{
		int idx = p - mem_;
		assert(idx >= 0 && idx < size_);
		used_[idx] = false;
		alloc_.destroy(p);
	}

};

#endif // !__MEMORY_POOL_H__