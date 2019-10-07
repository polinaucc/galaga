#pragma once
#include "livingobject.hpp"

class Player : public LivingObject
{
public:
	Player(double x, double y, unsigned int lives);
	virtual void on_tick() override {}
};
