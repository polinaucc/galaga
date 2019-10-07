#pragma once
#include "movingobject.hpp"
enum class BonusType
{
    life,
    score
};
class Bonus : public MovingObject
{
protected:
	BonusType m_type;
public:
    Bonus(double x, double y, double s, std::shared_ptr<Sprite> sprite, BonusType type):
        MovingObject(x, y, 0.0, s, sprite), m_type(type)
    {}
	virtual BonusType type() const { return m_type; }

    static shared_ptr<Bonus> create (double x, double y, double s, BonusType type);
};
