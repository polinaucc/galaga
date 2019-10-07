#pragma once
#include "Animation.hpp"

class DeathAnimation : public Animation
{
public:
    DeathAnimation(double x, double y, unsigned int current_sprite = 0);
};
