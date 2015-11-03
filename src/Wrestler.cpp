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

    current_state = 0;

    height = hit_height;
    width = hit_width;

    position.x = x;
    position.y = y;

    velocity.x = 0;
    velocity.y = 0;
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

void Wrestler::useGrab(Wrestler grabee)
{
    //Not done
}

void Wrestler::useThrow(Wrestler throwee)
{
    //Not done
}

void Wrestler::useDash()
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

int Wrestler::getCurrentState()
{
    return current_state;
}
void Wrestler::setCurrentState(int num)
{
    current_state = num;
}

Wrestler::~Wrestler()
{
    //dtor
}
