#include "Missile.hpp"
#include "spritestorage.hpp"

std::shared_ptr<Missile> Missile::create(double x, double y, double s, MissileType type)
{
    switch (type)
    {
        case MissileType::bad:
            return std::make_shared<Missile>(x, y, s, false, SpriteStorage::bad_m);
        case MissileType::good:
            return std::make_shared<Missile>(x, y, s, true, SpriteStorage::good_m);
        default:
            throw std::runtime_error("Unknows enemy type.");
    }
}
