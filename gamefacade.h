#pragma once
#include <list>
#include <memory>
#include "Controller.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"
#include "Animation.hpp"
#include "Bonus.hpp"

class GameFacade : public ControllerTemplateMethod
{
protected:
    GameFacade() {}
public:
    virtual Player const& player() const = 0;
    virtual list<shared_ptr<Enemy>> const& enemies() const = 0;
    virtual list<shared_ptr<Missile>> const& projectiles() const = 0;
    virtual list<shared_ptr<Animation>> const& animations() const = 0;
    virtual list<shared_ptr<Bonus>> const& bonuses() const = 0;

    virtual void tick() = 0;
    virtual unsigned int score() const = 0;

    virtual void save(string filename) = 0;
    virtual void load(string filename) = 0;
};
