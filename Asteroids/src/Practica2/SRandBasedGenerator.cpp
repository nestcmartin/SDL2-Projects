#include <assert.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "SRandBasedGenerator.h"

SRandBasedGenerator::SRandBasedGenerator() :
	seed_(std::time(0))
{
	init();
}

SRandBasedGenerator::SRandBasedGenerator(unsigned seed) :
	seed_(seed)
{
	init();
}

SRandBasedGenerator::~SRandBasedGenerator()
{
}

void SRandBasedGenerator::init()
{
	srand(seed_);
}

int SRandBasedGenerator::nextInt()
{
	return rand();
}

int SRandBasedGenerator::nextInt(int low, int high)
{
	assert(low < high);
	return low + (nextInt() % (high - low));
}