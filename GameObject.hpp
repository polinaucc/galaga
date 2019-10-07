#pragma once
#include <memory>
#include "sprite.hpp"
#include "tickable.hpp"

using namespace std;

class GameObject : public Tickable
{
protected:
    shared_ptr<Sprite> m_sprite;
	double m_x, m_y;
public:
    GameObject(double x, double y, shared_ptr<Sprite> sprite):
        m_x(x), m_y(y), m_sprite(sprite)
    {}
	double x() const { return m_x; }
	double y() const { return m_y; }
    virtual shared_ptr<Sprite> const sprite() const { return m_sprite; }

	virtual void move(double x, double limit);
	virtual void move(double x, double x_limit, double y, double y_limit);
};
