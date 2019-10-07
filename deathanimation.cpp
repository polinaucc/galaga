#include "deathanimation.hpp"
#include "spritestorage.hpp"

DeathAnimation::DeathAnimation(double x, double y, unsigned int current_sprite)
            : Animation(x, y, {
                        SpriteStorage::b1d,
                        SpriteStorage::b2d,
                        SpriteStorage::b3d,
                        SpriteStorage::b4d,
                        SpriteStorage::b5d
                }, current_sprite) {}
