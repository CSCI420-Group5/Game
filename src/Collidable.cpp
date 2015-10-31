#include "Collidable.h"

Collidable::Collidable()
{
    // ctor
}

void Collidable::init(int hit_height, int hit_width, int x, int y)
{
    id = reinterpret_cast<long int>(&id);

    height = hit_height;
    width = hit_width;

    position.x = x;
    position.y = y;

    velocity.x = 0;
    velocity.y = 0;
}

sf::Vector2f Collidable::getMovedPos()
{
    sf::Vector2f fin_pos;

    float mid = 0;
    if (velocity.x > 0) {
        mid = velocity.x + 1;
    }
    else if (velocity.x < 0) {
        mid = velocity.x - 1;
    }

    fin_pos.x = velocity.x + (int)mid;

    mid = 0;
    if (velocity.y > 0) {
        mid = velocity.y + 1;
    }
    else if (velocity.y < 0) {
        mid = velocity.y - 1;
    }

    fin_pos.y = velocity.y + (int)mid;

    return fin_pos;
}

void Collidable::move(float friction)
{
    sf::Vector2f fin_pos = getMovedPos();

    // check for walls and reverse speed inelastically if they hit
    if (fin_pos.x > 0 && fin_pos.x < (800-width)) {
        velocity.x = fin_pos.x;
    }
    else {
        velocity.x /= -2;
    }

    if (fin_pos.y > 0 && fin_pos.y < (600-height)) {
        velocity.y = fin_pos.y;
    }
    else {
        velocity.y /= -2;
    }

    // if movement is not zero, slow down based on friction
    if (velocity.x < 0) {
        if (velocity.x > (-friction)) {
            velocity.x = 0;
        }
        else {
            velocity.x = velocity.x + friction;
        }
    }
    else if (velocity.x > 0) {
        if (velocity.x < friction) {
            velocity.x = 0;
        }
        else {
            velocity.x = velocity.x - friction;
        }
    }

    if (velocity.y < 0) {
        if (velocity.y > (-friction)) {
            velocity.y = 0;
        }
        else {
            velocity.y = velocity.y + friction;
        }
    }
    else if (velocity.y > 0) {
        if (velocity.y < friction) {
            velocity.y = 0;
        }
        else {
            velocity.y = velocity.y - friction;
        }
    }
}

long int Collidable::getID() const
{
    return id;
}

int Collidable::getHeight() const
{
    return height;
}

int Collidable::getWidth() const
{
    return width;
}

void Collidable::setHeight(int num)
{
    height = num;
}

void Collidable::setWidth(int num)
{
    width = num;
}

sf::Vector2f Collidable::getPos() const
{
    return position;
}

sf::Vector2f Collidable::getVelocity() const
{
    return velocity;
}

void Collidable::setPos(float x, float y)
{
    position.x = x;
    position.y = y;
}

void Collidable::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

bool Collidable::operator < (const Collidable &obj) const
{
    return (position.y < obj.getPos().y);
}
