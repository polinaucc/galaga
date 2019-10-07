#include "Bonus.hpp"
#include "spritestorage.hpp"

std::shared_ptr<Bonus> Bonus::create(double x, double y, double s, BonusType type)
{
    switch (type)
        {
        case BonusType::life:
            return std::make_shared<Bonus>(x, y, s, SpriteStorage::heart, type);
        case BonusType::score:
            return std::make_shared<Bonus>(x, y, s, SpriteStorage::cherry, type);
        default:
            throw std::runtime_error("Unknows enemy type.");
    }
}
