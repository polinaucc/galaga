#include "Enemy.hpp"
#include "spritestorage.hpp"

shared_ptr<Sprite> const Enemy::sprite() const
{
    if (m_counter++ >= 20)
    {
		m_state = !m_state;
		m_counter = 0;
	}
	return m_state ? m_sprite : m_sprite_b;
}

shared_ptr<Enemy> Enemy:: create(double x, double y, EnemyType type)
{
    switch (type)
    {
        case EnemyType::green:
            return make_shared<GreenEnemy>(x, y);
        case EnemyType::purple:
            return make_shared<PurpleEnemy>(x, y);
        default:
            throw runtime_error("Unknows enemy type.");
    }
}

GreenEnemy::GreenEnemy(double x, double y):
    Enemy(x,y,SpriteStorage::b1a, SpriteStorage::b1b, 1, EnemyType::green)
{}

PurpleEnemy::PurpleEnemy(double x, double y):
    Enemy(x, y, SpriteStorage::b2a, SpriteStorage::b2b, 2, EnemyType::purple)
{}
