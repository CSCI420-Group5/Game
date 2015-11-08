#include "Wrestler.h"
#include "SFML/Graphics.hpp"

Wrestler::Wrestler()
{
    //ctor
}

void Wrestler::init(int hit_height, int hit_width, int x, int y)
{
    //Maybe should be a more unique id
    id = reinterpret_cast<long int>(&id);

    current_state = NORMAL;
    frozen_frames = 0;

    id_of_grabbed = 0;

    height = hit_height;
    width = hit_width;

    position.x = x;
    position.y = y;

    velocity.x = 0;
    velocity.y = 0;

    stamina = 100;
}

sf::ConvexShape Wrestler::getPath()
{
    int fin_x = getMovedPos().x;
    int fin_y = getMovedPos().y;

    sf::ConvexShape path;
    path.setPointCount(4);
    path.setPoint(0, sf::Vector2f(fin_x, fin_y));
    path.setPoint(1, sf::Vector2f(position));
    path.setPoint(2, sf::Vector2f(position.x+width, position.y+height));
    path.setPoint(3, sf::Vector2f(fin_x+width, fin_y+height));

    return path;
}

void Wrestler::useGrab(Wrestler* grabee)
{
    current_state = GRABBING;
    grabee->setCurrentState(Wrestler::GRABBED);

    //Stop actors' movement
    grabee->setVelocity(0, 0);
    setVelocity(0, 0);

    id_of_grabbed = grabee->getID();

    resetFrozenFrames();
    grabee->resetFrozenFrames();

    stamina -= 25;
}

void Wrestler::useThrow(Wrestler* throwee)
{
    // up / right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        throwee->setVelocity(6, -6);
    }

    // down / right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        throwee->setVelocity(6, 6);
    }

    // down / left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        throwee->setVelocity(-6, 6);
    }

    // up / left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        throwee->setVelocity(-6, -6);
    }

    // up
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        throwee->setVelocity(0, -12);
    }

    // down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        throwee->setVelocity(0, 12);
    }

    // left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        throwee->setVelocity(-12, 0);
    }

    // right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        throwee->setVelocity(12, 0);
    }

    current_state = NORMAL;
    throwee->setCurrentState(Wrestler::THROWN);
    throwee->resetFrozenFrames();
}

void Wrestler::increaseStamina()
{
    if (stamina < 100)
    {
        stamina += 1;
    }
}

void Wrestler::useDash()
{
    if (stamina > 49)
    {
         // up / right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                velocity.x = 6;
                velocity.y = -6;
            }

        // down / right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                velocity.x = 6;
                velocity.y = 6;
            }

        // down / left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                velocity.x =-6;
                velocity.y = 6;
            }

        // up / left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                velocity.x = -6;
                velocity.y = -6;
            }

            // up
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                velocity.x = 0;
                velocity.y = -12;
            }

            // down
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                velocity.x = 0;
                velocity.y = 12;
            }

            // left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                velocity.x = -12;
                velocity.y = 0;
            }

            // right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                velocity.x = 12;
                velocity.y = 0;
            }

        stamina -= 50;
    }

    current_state = DASH;
    resetFrozenFrames();
}

int Wrestler::getSpeed()
{
    return speed;
}
int Wrestler::getStrength()
{
    return strength;
}
int Wrestler::getWeight()
{
    return weight;
}
int Wrestler::getStamina()
{
    return stamina;
}
float Wrestler::getAcceleration()
{
    return acceleration;
}

void Wrestler::setStats(int spd, int str, int wgt, int stm)
{
    speed = spd;
    strength = str;
    weight = wgt;
    stamina = stm;
    acceleration = float(str) / float(wgt);
}

Wrestler::State Wrestler::getCurrentState()
{
    return current_state;
}
void Wrestler::setCurrentState(State new_state)
{
    current_state = new_state;
}
void Wrestler::incFrozenFrames()
{
    frozen_frames++;
}
void Wrestler::resetFrozenFrames()
{
    frozen_frames = 0;
}
int Wrestler::getFrozenFrames()
{
    return frozen_frames;
}
long int Wrestler::getIDOfGrabbed()
{
    return id_of_grabbed;
}
void Wrestler::setIDOfGrabbed(long int id)
{
    id_of_grabbed = id;
}

Wrestler::~Wrestler()
{
    //dtor
}
