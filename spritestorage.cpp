#include "spritestorage.hpp"
void SpriteStorage::load() {
    b1a = make_shared<Sprite>(":/img/b1a");
    b1b = make_shared<Sprite>(":/img/b1b");
    b2a = make_shared<Sprite>(":/img/b2a");
    b2b = make_shared<Sprite>(":/img/b2b");

    b1d = make_shared<Sprite>(":/img/b1d");
    b2d = make_shared<Sprite>(":/img/b2d");
    b3d = make_shared<Sprite>(":/img/b3d");
    b4d = make_shared<Sprite>(":/img/b4d");
    b5d = make_shared<Sprite>(":/img/b5d");

    bad_m = make_shared<Sprite>(":/img/bad_m");
    good_m = make_shared<Sprite>(":/img/good_m");

    ship = make_shared<Sprite>(":/img/ship");
    space =make_shared<Sprite>(":/img/space");

    cherry =make_shared<Sprite>(":/img/cherry");
    heart = make_shared<Sprite>(":/img/heart");
}

shared_ptr<Sprite> SpriteStorage::b1a;
shared_ptr<Sprite> SpriteStorage::b1b;
shared_ptr<Sprite> SpriteStorage::b2a;
shared_ptr<Sprite> SpriteStorage::b2b;

shared_ptr<Sprite> SpriteStorage::b1d;
shared_ptr<Sprite> SpriteStorage::b2d;
shared_ptr<Sprite> SpriteStorage::b3d;
shared_ptr<Sprite> SpriteStorage::b4d;
shared_ptr<Sprite> SpriteStorage::b5d;

shared_ptr<Sprite> SpriteStorage::bad_m;
shared_ptr<Sprite> SpriteStorage::good_m;

shared_ptr<Sprite> SpriteStorage::ship;
shared_ptr<Sprite> SpriteStorage::space;

shared_ptr<Sprite> SpriteStorage::cherry;
shared_ptr<Sprite> SpriteStorage::heart;
