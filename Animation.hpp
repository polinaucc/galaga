#pragma once
#include <vector>
#include "GameObject.hpp"


enum class AnimationType
{
    death
};

class Animation : public GameObject
{
private:
    vector<shared_ptr<Sprite>> m_sprites;
	mutable unsigned int m_current_sprite;
    mutable unsigned int m_counter; //счетчик тиков
public:
    Animation(double x, double y, vector<shared_ptr<Sprite>> sprites, unsigned int current_sprite = 0);
    virtual shared_ptr<Sprite> const sprite() const override;
	bool is_over() const { return m_current_sprite >= m_sprites.size(); }
    virtual void on_tick() override {}

    static shared_ptr<Animation> create (double x, double y, AnimationType type = AnimationType::death);
};
