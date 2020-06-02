#ifndef __FOOD_SYSTEM_H__
#define __FOOD_SYSTEM_H__

#include "System.h"

class FoodSystem : public System 
{
private:
	int numOfFoodPieces_;

public:
	FoodSystem();

	void init() override;
	void update() override;
	void receive(const msg::Message& msg) override;

private:
	void addFood(std::size_t n);
	void onEat(Entity *e);
	void disableAll();
};

#endif // !__FOOD_SYSTEM_H__