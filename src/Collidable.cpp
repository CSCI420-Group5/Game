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

    off_edge = true;

    position.x = x;
    position.y = y;

    velocity.x = 0;
    velocity.y = 0;

    speed = 100;
    weight = 10;
}

sf::Vector2f Collidable::getMovedPos(int level_w, int level_h)
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
    else if (fin_pos.x >= (level_w-width)) {
        fin_pos.x = level_w - width;
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
    else if (fin_pos.y >= (level_h-height)) {
        fin_pos.y = level_h - height;
    }

    return fin_pos;
}

void Collidable::move(float friction, int level_w, int level_h)
{
    sf::Vector2f fin_pos = getMovedPos(level_w, level_h);

    // check for walls and reverse speed inelastically if they hit
    if (fin_pos.x == 1 || fin_pos.x == level_w - width) {
        velocity.x /= -2;
    }
    if (fin_pos.y == 1 || fin_pos.y == level_h - height) {
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

std::string Collidable::getName()
{
    return name;
}

void Collidable::setName(std::string actor_name)
{
    name = actor_name;
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

bool Collidable::offEdge()
{
    return off_edge;
}

void Collidable::setOffEdge(bool val)
{
    off_edge = val;
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

void Collidable::setVelocity(float x, float y, int level_w, int level_h)
{
    //Don't go above the top speed
    if (x > speed){
        velocity.x = speed;
    }
    else{
        velocity.x = x;
    }
    if (y > speed){
        velocity.y = speed;
    }
    else{
        velocity.y = y;
    }

    //Reflect if moving off screen
    sf::Vector2f moved_pos = getMovedPos(level_w, level_h);

    if(moved_pos.x == 1 || moved_pos.x == level_w - width){
        velocity.x /= -2;
    }
    if(moved_pos.y == 1 || moved_pos.y == level_h - height){
        velocity.y /= -2;
    }
}

float Collidable::getSpeed()
{
    return speed;
}
float Collidable::getWeight()
{
    return weight;
}

Collidable::~Collidable()
{
    //dtor
}
