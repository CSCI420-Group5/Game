#include <cstdlib>
#include <cmath>
#include <iostream>

#include "Projectile.h"

sf::Vector2f getRandDir()
{
    // get a vector with values between -RAND_MAX and RAND_MAX
    sf::Vector2f vector;
    vector.x = rand() - (RAND_MAX / 2);
    vector.y = rand() - (RAND_MAX / 2);

    float magnitude = sqrt((vector.x*vector.x)+(vector.y+vector.y));

    // normalize the vector
    return sf::Vector2f(vector.x/magnitude, vector.y/magnitude);
}

Projectile::Projectile()
{
    // ctor
}

void Projectile::init(int hit_height, int hit_width, int x, int y)
{
    id = reinterpret_cast<long int>(&id);

    height = hit_height;
    width = hit_width;

    position.x = x;
    position.y = y;

    ball_pos.x = x;
    ball_pos.y = y;

    has_shot = false;
}

sf::Vector2f Projectile::getBallPos() const
{
    return ball_pos;
}

sf::Vector2f Projectile::getBallVel() const
{
    return ball_vel;
}

void Projectile::setBallPos(float x, float y)
{
    ball_pos.x = x;
    ball_pos.y = y;
}

void Projectile::setBallVel(float x, float y)
{
    ball_vel.x = x;
    ball_vel.y = y;
}

bool Projectile::hasShot()
{
    return has_shot;
}

void Projectile::setHasShot(bool val)
{
    has_shot = val;
}

void Projectile::shootBall()
{
    ball_pos.x = position.x;
    ball_pos.y = position.y;

    ball_vel = getRandDir();
    moveBall(ball_vel.x+1, ball_vel.y+1);
}

void Projectile::moveBall(float x, float y)
{
    ball_pos.x += x;
    ball_pos.y += y;
}

Projectile::Dir Projectile::getDir()
{
    return dir;
}

void Projectile::setDir(Dir d)
{
    dir = d;
}

Projectile::SpriteState Projectile::getState()
{
    return state;
}

void Projectile::setState(Projectile::SpriteState s)
{
    state = s;
}
