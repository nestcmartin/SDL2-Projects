#ifndef __RANDOM_NUMBER_GENERATOR_H__
#define __RANDOM_NUMBER_GENERATOR_H__

class RandomNumberGenerator 
{
public:
	RandomNumberGenerator();
	virtual ~RandomNumberGenerator();

	virtual void init() = 0;
	virtual int nextInt() = 0;
	virtual int nextInt(int low, int high) = 0;
};

#endif // !__RANDOM_NUMBER_GENERATOR_H__