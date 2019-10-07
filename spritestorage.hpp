#pragma once
#include "sprite.hpp"
using namespace std;
struct SpriteStorage
{
public:
    static shared_ptr<Sprite> b1a;
    static shared_ptr<Sprite> b1b;
    static shared_ptr<Sprite> b2a;
    static shared_ptr<Sprite> b2b;

    static shared_ptr<Sprite> b1d;
    static shared_ptr<Sprite> b2d;
    static shared_ptr<Sprite> b3d;
    static shared_ptr<Sprite> b4d;
    static shared_ptr<Sprite> b5d;

    static shared_ptr<Sprite> bad_m;
    static shared_ptr<Sprite> good_m;

    static shared_ptr<Sprite> ship;
    static shared_ptr<Sprite> space;

    static shared_ptr<Sprite> cherry;
    static shared_ptr<Sprite> heart;

    static void load();

    SpriteStorage() = delete;
};
