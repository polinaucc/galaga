#include "Animation.hpp"
#include "sprite.hpp"
#include "deathanimation.hpp"

Animation::Animation(double x, double y, vector<shared_ptr<Sprite>> sprites, unsigned int current_sprite):
    GameObject(x,y, sprites.front()), m_sprites(sprites), m_current_sprite(current_sprite), m_counter(0)
{
    if (current_sprite >= sprites.size())
        throw runtime_error("Incorrect current sprite was requested.");
}

shared_ptr<Sprite> const Animation::sprite() const
{
    if (m_counter++ >= 20)
    {
        m_current_sprite++;
        m_counter = 0;
    }

    if (is_over())
        return nullptr;
    else
        return m_sprites.at(m_current_sprite);  //доступ к элементу с проверкй выхода за границу
}


shared_ptr<Animation> Animation::create(double x, double y, AnimationType type)
{
    switch (type)
    {
        case AnimationType::death:
            return make_shared<DeathAnimation>(x, y);
        default:
            throw runtime_error("Unknown animation type.");
    }
}
