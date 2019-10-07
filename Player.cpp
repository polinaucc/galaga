#include "Player.hpp"
#include "spritestorage.hpp"

Player::Player(double x, double y, unsigned int lives) :
    LivingObject(x, y, SpriteStorage::ship, lives)
{}
