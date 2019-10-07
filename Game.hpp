#pragma once
#include <list>
#include <functional>
#include "Player.hpp"
#include "Controller.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"
#include "Animation.hpp"
#include "Bonus.hpp"
#include "gamefacade.h"

using namespace std;

class Game : public GameFacade
{
private:
    unique_ptr<Player> m_player;
    list<shared_ptr<Enemy>> m_enemies;
    list<shared_ptr<Missile>> m_projectiles;
    list<shared_ptr<Animation>> m_animations;
    list<shared_ptr<Bonus>> m_bonuses;

    unsigned int m_current_cooldown; //сколько тактов прошло от последнего выстрела ракеты
	unsigned int m_score;
	unsigned int m_tick_counter;
    unsigned int m_kill_counter;
    double m_shift; //на сколько враги сдвинуты от центра

	static double m_width, m_height;
    static function<void(bool, unsigned int)> end_game;
    static shared_ptr<Game> m_instance; //Чтобы контролировать существование единственного объекта, указатель на него статически хранится внутри. (закрітій атрибут)
private:
    Game() {} //конструктор (единственній)
public:
    static void initialize(double width, double height, function<void(bool, unsigned int)> end_game); //метод инициализации
    static shared_ptr<Game> get_instance() //метод доступа
    {
        if(!m_instance)
            initialize(m_width, m_height, [](bool,unsigned int){});
        return m_instance;
    }

    virtual Player const& player() const override { return *m_player; }
    virtual list<shared_ptr<Enemy>> const& enemies() const override { return m_enemies; }
    virtual list<shared_ptr<Missile>> const& projectiles() const override { return m_projectiles; }
    virtual list<shared_ptr<Animation>> const& animations() const override { return m_animations; }
    virtual list<shared_ptr<Bonus>> const& bonuses() const override { return m_bonuses; }

    virtual void tick() override;
    virtual unsigned int score() const override { return m_score; }
	void add_enemy(double x, double y, EnemyType type);
	void add_enemy(double x, double y);
	void add_enemies();
	
    virtual void save(string filename) override;
    virtual void load(string filename) override;

    virtual void left_action() override;
    virtual void right_action() override;
    virtual void shoot_action() override;
public:
	//Constants:
	double const move_per_tick = 15.0;
	double const projectile_speed = 15.0;
	unsigned int const projectile_cooldown = 9;

	double const chance_to_spawn_an_enemy = 0.07;
	double const enemy_field_percent = 0.7;
	double const hitbox_size = 20.0;

    unsigned int const enemy_rows = 12;
	double const chance_of_enemy_missile = 0.0005;
	double const chance_of_enemy_moving = 0.03;

	double const chance_of_bonus = 0.1;
	double const bonus_speed = 5.0;

    unsigned int const level_wait = 200;

    unsigned int const kills_to_win = 40;
};
