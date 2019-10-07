#pragma once
#include "GameObject.hpp"

class LivingObject : public GameObject
{
protected:
    mutable unsigned int m_lives;
public:
    LivingObject(double x, double y, std::shared_ptr<Sprite> sprite, unsigned int lives):
        GameObject(x, y, sprite), m_lives(lives)
    {}
    unsigned int lives() const { return m_lives; }
    void die() { if (m_lives) m_lives--; }
    void add_life() { m_lives++; }
    bool is_alive() const { return lives(); }
};
