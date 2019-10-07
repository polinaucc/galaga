#pragma once
#include "movingobject.hpp"

enum class MissileType
{
    good,
    bad
};

class Missile : public MovingObject
{
protected:
	bool is_good;
public:
    Missile(double x, double y, double s, bool is_good, shared_ptr<Sprite> sprite):
        MovingObject(x, y, 0.0, s, sprite), is_good(is_good)
    {}
	double speed() const { return speed_y(); }
	bool good() const { return is_good; }

    static shared_ptr<Missile> create(double x, double y, double s, MissileType type);
};
