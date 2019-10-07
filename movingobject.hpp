#pragma once
#include "GameObject.hpp"

class MovingObject : public GameObject
{
protected:
    double m_speed_x, m_speed_y;
public:
    MovingObject(double x, double y, double s_x, double s_y, std::shared_ptr<Sprite> sprite):
        GameObject(x, y, sprite), m_speed_x(s_x), m_speed_y(s_y)
    {}
    double speed_x() const { return m_speed_x; }
    double speed_y() const { return m_speed_y; }
    virtual void on_tick() override {
        m_x += m_speed_x;
        m_y += m_speed_y;
    }
};
