#pragma once
#include "livingobject.hpp"

enum class EnemyType
{
    green,
    purple
};
class Enemy : public LivingObject
{
private:
	mutable bool m_state;
	mutable int m_counter;
	EnemyType m_type;
protected:
    shared_ptr<Sprite> m_sprite_b;
public:
    Enemy(double x, double y, shared_ptr<Sprite> s1, shared_ptr<Sprite> s2, unsigned int lives, EnemyType type):
        LivingObject(x, y, s1, lives), m_sprite_b(s2), m_state(false), m_counter(0), m_type(type)
    {}

    virtual shared_ptr<Sprite> const sprite() const override;
	virtual void on_tick() override {}
    virtual EnemyType type() const {return m_type; }

    static shared_ptr<Enemy> create(double x, double y, EnemyType type);
};

class GreenEnemy: public Enemy
{
public:
    GreenEnemy(double x, double y);
};

class PurpleEnemy: public Enemy
{
public:
    PurpleEnemy(double x, double y);
};
