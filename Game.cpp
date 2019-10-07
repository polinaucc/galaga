#include <random>
#include "Game.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"
#include <algorithm>
#include <string>
#include <fstream>

mt19937_64 random(random_device{}());
uniform_real_distribution<> percent(0.0, 1.0);
bernoulli_distribution boolean(0.5);

double Game::m_width, Game::m_height;
function<void(bool, unsigned int)> Game::end_game;
shared_ptr<Game> Game::m_instance;

void Game::initialize(double width, double height, function<void(bool, unsigned int)> _end_game)
{
	if (m_instance)
        throw runtime_error("Game was already initialized.");
    m_instance = shared_ptr<Game>(new Game());
	m_instance->is_left = false;
	m_instance->is_right = false;
	m_instance->is_shoot = false;
	m_instance->m_current_cooldown = 0;
	m_instance->m_width = width;
	m_instance->m_height = height;
	m_instance->m_score = 0;
	m_instance->m_tick_counter = 0;
    m_instance->m_kill_counter=0;
    m_instance->end_game = _end_game;
	m_instance->m_shift = 0;
    m_instance->m_player = unique_ptr<Player>(new Player(width * 0.5, height * 0.9, 3));
}

void Game::add_enemy(double x, double y, EnemyType type)
{
    m_enemies.push_back(Enemy::create(x, y, type));
}
void Game::add_enemy(double x, double y)
{
	return add_enemy(x, y, boolean(random) ? EnemyType::green : EnemyType::purple);
}
void Game::add_enemies()
{
    if (m_tick_counter == level_wait)
    {
		add_enemy(m_width * 0.515 + m_shift, m_height * 0.31);
		add_enemy(m_width * 0.485 + m_shift, m_height * 0.31);
		add_enemy(m_width * 0.515 + m_shift, m_height * 0.34);
		add_enemy(m_width * 0.485 + m_shift, m_height * 0.34);

		add_enemy(m_width * 0.515 + m_shift, m_height * 0.37);
		add_enemy(m_width * 0.485 + m_shift, m_height * 0.37);
		add_enemy(m_width * 0.515 + m_shift, m_height * 0.40);
		add_enemy(m_width * 0.485 + m_shift, m_height * 0.40);
	}

    if (m_tick_counter == level_wait * 2)
    {
		add_enemy(m_width * 0.515 + m_shift, m_height * 0.28);
		add_enemy(m_width * 0.485 + m_shift, m_height * 0.28);
		add_enemy(m_width * 0.545 + m_shift, m_height * 0.28);
		add_enemy(m_width * 0.455 + m_shift, m_height * 0.28);

		add_enemy(m_width * 0.545 + m_shift, m_height * 0.31);
		add_enemy(m_width * 0.455 + m_shift, m_height * 0.31);
		add_enemy(m_width * 0.545 + m_shift, m_height * 0.34);
		add_enemy(m_width * 0.455 + m_shift, m_height * 0.34);
	}
    if (m_tick_counter == level_wait * 3)
    {
		add_enemy(m_width * 0.575 + m_shift, m_height * 0.31);
		add_enemy(m_width * 0.425 + m_shift, m_height * 0.31);
		add_enemy(m_width * 0.575 + m_shift, m_height * 0.34);
		add_enemy(m_width * 0.425 + m_shift, m_height * 0.34);

		add_enemy(m_width * 0.605 + m_shift, m_height * 0.31);
		add_enemy(m_width * 0.395 + m_shift, m_height * 0.31);
		add_enemy(m_width * 0.605 + m_shift, m_height * 0.34);
		add_enemy(m_width * 0.395 + m_shift, m_height * 0.34);
	}
    if (m_tick_counter == level_wait * 4)
    {
		add_enemy(m_width * 0.545 + m_shift, m_height * 0.37);
		add_enemy(m_width * 0.455 + m_shift, m_height * 0.37);
		add_enemy(m_width * 0.545 + m_shift, m_height * 0.40);
		add_enemy(m_width * 0.455 + m_shift, m_height * 0.40);

		add_enemy(m_width * 0.575 + m_shift, m_height * 0.37);
		add_enemy(m_width * 0.425 + m_shift, m_height * 0.37);
		add_enemy(m_width * 0.575 + m_shift, m_height * 0.40);
		add_enemy(m_width * 0.425 + m_shift, m_height * 0.40);
	}
    if (m_tick_counter == level_wait * 5)
    {
		add_enemy(m_width * 0.605 + m_shift, m_height * 0.37);
		add_enemy(m_width * 0.395 + m_shift, m_height * 0.37);
		add_enemy(m_width * 0.605 + m_shift, m_height * 0.40);
		add_enemy(m_width * 0.395 + m_shift, m_height * 0.40);

		add_enemy(m_width * 0.635 + m_shift, m_height * 0.37);
		add_enemy(m_width * 0.365 + m_shift, m_height * 0.37);
		add_enemy(m_width * 0.635 + m_shift, m_height * 0.40);
		add_enemy(m_width * 0.365 + m_shift, m_height * 0.40);
	}
	/*
	if (percent(random) <= chance_to_spawn_an_enemy)
		if (boolean(random))
			m_enemies.push_back(create_enemy(m_width / (enemy_rows + 1) * x_pos(random),
											 y_pos(random),
											 1));
		else
			m_enemies.push_back(create_enemy(m_width / (enemy_rows + 1) * x_pos(random),
											 y_pos(random),
											 2));
	*/
}


void Game::tick()
{
	add_enemies();
	m_tick_counter++;
    process_events();

		if (m_current_cooldown != 0)
			m_current_cooldown--;

		m_player->on_tick();

	bool is_moving = percent(random) <= chance_of_enemy_moving;
	bool left_or_right = boolean(random);
	if (is_moving)
		m_shift += left_or_right ? move_per_tick : -move_per_tick;
    for (auto enemy : m_enemies)
    {
		enemy->on_tick();
		for (auto projectile : m_projectiles)
			if (
				enemy->is_alive() &&
				projectile->good() &&
				fabs(projectile->x() - enemy->x()) < hitbox_size &&
				fabs(projectile->y() - enemy->y()) < hitbox_size * 2
			) {
				m_projectiles.remove(projectile);
				enemy->die();
				m_score += 1;
                if (!enemy->is_alive())
                    if (++m_kill_counter >= kills_to_win)
                    {
                        end_game(true, m_score);
                        discard_events();
                     }
				if (percent(random) <= chance_of_bonus)
                    m_bonuses.push_back(Bonus::create(enemy->x(), enemy->y(), bonus_speed,
													   boolean(random) ? BonusType::life : BonusType::score));
				break;
			}
		if (percent(random) <= chance_of_enemy_missile)
            m_projectiles.push_back(Missile::create(enemy->x(), enemy->y(), +projectile_speed, MissileType::bad));
		if (is_moving)
        {
			if (left_or_right)
				enemy->move(move_per_tick, m_width, 0, 0);
			else
				enemy->move(-move_per_tick, 0, 0, 0);
         }
		if (!enemy->is_alive())
            m_animations.push_back(Animation::create(enemy->x(), enemy->y()));
	}
    for (auto projectile : m_projectiles)
    {
		projectile->on_tick();
		if (
			m_player->is_alive() &&
			!projectile->good() &&
			fabs(projectile->x() - m_player->x()) < hitbox_size &&
			fabs(projectile->y() - m_player->y()) < hitbox_size * 2
		) {
			m_projectiles.remove(projectile);
			m_player->die();
			if (!m_player->is_alive())
                end_game(false, m_score);
                discard_events();
			break;
		}
	}
    for (auto bonus : m_bonuses)
    {
		bonus->on_tick();
		if (
			m_player->is_alive() &&
			fabs(bonus->x() - m_player->x()) < hitbox_size &&
			fabs(bonus->y() - m_player->y()) < hitbox_size * 2
			) {
            switch (bonus->type())
            {
				case BonusType::life:
					m_player->add_life();
				case BonusType::score:
					m_score += 10;
			}
			m_bonuses.remove(bonus);
			break;
		}
	}

    m_projectiles.remove_if([this](shared_ptr<Missile> projectile) -> bool { return projectile->y() <= 0.0 || projectile->y() >= m_height; });
    m_enemies.remove_if([this](shared_ptr<Enemy> enemy) -> bool { return !enemy->is_alive(); });
    m_animations.remove_if([this](shared_ptr<Animation> animation) -> bool { return animation->is_over(); });
    m_bonuses.remove_if([this](shared_ptr<Bonus> bonus) -> bool { return bonus->y() <= 0.0 || bonus->y() >= m_height; });
}


void Game::save(string filename)
{
    ofstream f(filename);
    if (!f)
        throw std::runtime_error("Cannot open save file");
    f << "MyGalaga_save_file_v0.1\n";
    f << m_width << ' ' << m_height << ' ' << m_current_cooldown << ' ' <<
        m_score << ' ' << m_tick_counter << ' ' << m_kill_counter << " " << m_shift << '\n';
    f << m_player->x() << ' ' << m_player->y() << ' ' << m_player->lives() << '\n';
    f << m_enemies.size() << '\n';
    for (auto enemy : m_enemies)
        f << static_cast<size_t>(enemy->type()) << ' ' << enemy->x() << ' ' << enemy->y() << '\n';
    f << m_projectiles.size() << '\n';
    for (auto projectile : m_projectiles)
        f << projectile->x() << ' ' << projectile->y() << ' ' << projectile->speed() << ' ' << projectile->good() << '\n';
    f << m_bonuses.size() << '\n';
    for (auto bonus : m_bonuses)
        f << bonus->x() << ' ' << bonus->y() << ' ' << bonus->speed_y() << ' ' << static_cast<size_t>(bonus->type()) << '\n';
    f << "MyGalaga_save_file_v0.1\n";
}

void Game::load(string filename)
{
    ifstream f(filename);
	if (!f)
		throw std::runtime_error("Cannot open save file");
    string temp;
	f >> temp;
	if (temp != "MyGalaga_save_file_v0.1")
        throw runtime_error("This save file isn't supported.");
	f >> m_width >> m_height >> m_current_cooldown >> 
        m_score >> m_tick_counter >> m_kill_counter >> m_shift;

	double x, y;
	unsigned int lives;
	f >> x >> y >> lives;
    m_player = std::unique_ptr<Player>(new Player(x, y, lives));

	int size, type;
	f >> size;
	m_enemies.clear();
	for (int i = 0; i < size; i++) {
		f >> type >> x >> y;
		add_enemy(x, y, EnemyType(type));
	}

	double speed;
	bool good;
	f >> size;
	m_projectiles.clear();
    for (int i = 0; i < size; i++)
    {
		f >> x >> y >> speed >> good;
		if (good)
            m_projectiles.push_back(Missile::create(x, y, speed, MissileType::good));
		else
            m_projectiles.push_back(Missile::create(x, y, speed, MissileType::bad));
	}
	f >> size;
	m_bonuses.clear();
    for (int i = 0; i < size; i++)
    {
		f >> x >> y >> speed >> type;
        m_bonuses.push_back(Bonus::create(x, y, speed, BonusType(type)));
	}
	f >> temp;
	if (temp != "MyGalaga_save_file_v0.1")
        throw runtime_error("This save file isn't supported.");
    discard_events();
}

void Game::left_action()
{
    m_player->move(-move_per_tick,0);
}

void Game::right_action()
{
    m_player->move(move_per_tick, m_width);
}
void Game::shoot_action()
{
    if(!m_current_cooldown)
    {
        m_projectiles.push_back(Missile::create(m_player->x(), m_player->y(), -projectile_speed, MissileType::good));
        m_current_cooldown=projectile_cooldown;
    }
}


