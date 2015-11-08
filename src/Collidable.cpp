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

    //For x
    float mid = 0;
    if (velocity.x > 0) {
        mid = velocity.x + 1;
    }
    else if (velocity.x < 0) {
        mid = velocity.x - 1;
    }

    fin_pos.x = position.x + (int)mid;

    //Cannot move x off screen
    if (fin_pos.x <= 0) {
        fin_pos.x = 1;
    }
    else if (fin_pos.x >= (800-width)) {
        fin_pos.x = 799 - width;
    }

    //For y
    mid = 0;
    if (velocity.y > 0) {
        mid = velocity.y + 1;
    }
    else if (velocity.y < 0) {
        mid = velocity.y - 1;
    }

    fin_pos.y = position.y + (int)mid;

    //Cannot move y off screen
    if (fin_pos.y <= 0) {
        fin_pos.y = 1;
    }
    else if (fin_pos.y >= (600-height)) {
        fin_pos.y = 599 - height;
    }

    return fin_pos;
}

void Collidable::move(float friction)
{
    sf::Vector2f fin_pos = getMovedPos();

    // check for walls and reverse speed inelastically if they hit
    if (fin_pos.x == 1 || fin_pos.x == 799 - width) {
        velocity.x /= -2;
    }
    if (fin_pos.y == 1 || fin_pos.y == 599 - height) {
        velocity.y /= -2;
    }

    position.x = fin_pos.x;
    position.y = fin_pos.y;

    // if movement is not zero, slow down based on friction
    if (velocity.x < 0) {
        if (velocity.x > (-friction))
            velocity.x = 0;
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

bool Collidable::isWrestler()
{
    return is_wrestler;
}

void Collidable::setIsWrestler(bool val)
{
    is_wrestler = val;
}

bool Collidable::hasProjectile()
{
    return has_projectile;
}

void Collidable::setHasProjectile(bool val)
{
    has_projectile = val;
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

void Collidable::setCurrentState(int num)
{
    current_state = num;
}

int Collidable::getCurrentState()
{
    return current_state;
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

    //Reflect if moving off screen
    sf::Vector2f moved_pos = getMovedPos();

    if(moved_pos.x == 1 || moved_pos.x == 799 - width){
        velocity.x /= -2;
    }
    if(moved_pos.y == 1 || moved_pos.y == 599 - height){
        velocity.y /= -2;
    }
}

/*bool Collidable::operator < (const Collidable &obj) const
{
    return (position.y < obj.getPos().y);
}
*/
