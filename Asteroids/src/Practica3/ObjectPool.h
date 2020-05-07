#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include <cassert>
#include <vector>
#include <list>

// Clase para gestionar el estado de activación de varios objetos de tipo T
template<typename T>
class ObjectPool 
{
private:
	T* objs_;					// Pool de objetos de tipo T
	std::size_t size_;			// Número de objetos de tipo T del pool
	std::list<T*> free_;		// Lista de referencias a objetos disponibles
	std::vector<T*> objsPtrs_;	// Lista de referencias a todos los objetos del pool

public:
	// Constructora
	// Crea un pool de size objetos de tipo T
	ObjectPool(std::size_t size) 
	{
		size_ = size;
		objs_ = new T[size_];
		for (auto i(0u); i < size_; i++) 
		{
			objsPtrs_.push_back(&objs_[i]);
			free_.push_back(&objs_[i]);
		}
	}

	// Destructora
	// Elimina todos los objetos de tipo T del pool
	virtual ~ObjectPool() 
	{
		delete[] objs_;
	}

	// Devuelve el primer objeto de tipo T disponible en el pool
	T* getObject() 
	{
		if (!free_.empty()) 
		{
			T* o = free_.front();
			free_.pop_front();
			return o;
		} 
		
		return nullptr;
	}

	// Devuelve al pool el objeto de tipo T indicado
	void releaseObject(T* p) 
	{
		std::size_t idx = p - objs_;
		assert(idx >= 0 && idx < size_);
		free_.push_back(p);
	}

	// Accede a la lista de referencias a todos los objetos del pool
	const std::vector<T*>& getPool() 
	{
		return objsPtrs_;
	}
};

#endif // !__OBJECT_POOL_H__