#ifndef __SRANDOM_NUMBER_GENERATOR_H__
#define __SRANDOM_NUMBER_GENERATOR_H__

#include "RandomNumberGenerator.h"

class SRandBasedGenerator : public RandomNumberGenerator
{
private:
	unsigned seed_;

public:
	SRandBasedGenerator();
	SRandBasedGenerator(unsigned seed);
	virtual ~SRandBasedGenerator();

	virtual void init();

	virtual int nextInt();
	virtual int nextInt(int low, int high);	// Low incluido, High no incluido
};

#endif // !__SRANDOM_NUMBER_GENERATOR_H__