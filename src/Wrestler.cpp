#include "Wrestler.h"
#include "SFML/Graphics.hpp"
#include <cmath>

Wrestler::Wrestler()
{
    //ctor
}

void Wrestler::init(int hit_height, int hit_width, int x, int y)
{
    //Maybe should be a more unique id
    id = reinterpret_cast<long int>(&id);

    current_state = NORMAL;
    sprite_state = STAND_RIGHT;
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
    int str = 12;

    // up / right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        throwee->setVelocity(str/std::sqrt(2), -str/std::sqrt(2));
    }

    // down / right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        throwee->setVelocity(str/std::sqrt(2), str/std::sqrt(2));
    }

    // down / left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        throwee->setVelocity(-str/std::sqrt(2), str/std::sqrt(2));
    }

    // up / left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
        && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        throwee->setVelocity(-str/std::sqrt(2), -str/std::sqrt(2));
    }

    // up
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        throwee->setVelocity(0, -str);
    }

    // down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        throwee->setVelocity(0, str);
    }

    // left
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        throwee->setVelocity(-str, 0);
    }

    // right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        throwee->setVelocity(str, 0);
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
    int spd = 12;

    if (stamina > 49)
    {
         // up / right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                velocity.x = spd/std::sqrt(2);
                velocity.y = -spd/std::sqrt(2);
                setCurSpriteState(DASH_RIGHT);
            }

        // down / right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                velocity.x = spd/std::sqrt(2);
                velocity.y = spd/std::sqrt(2);
                setCurSpriteState(DASH_RIGHT);
            }

        // down / left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                velocity.x = -spd/std::sqrt(2);
                velocity.y = spd/std::sqrt(2);
                setCurSpriteState(DASH_LEFT);
            }

        // up / left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
            && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                velocity.x = -spd/std::sqrt(2);
                velocity.y = -spd/std::sqrt(2);
                setCurSpriteState(DASH_LEFT);
            }

            // up
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                velocity.x = 0;
                velocity.y = -spd;
                setCurSpriteState(DASH_UP);
            }

            // down
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                velocity.x = 0;
                velocity.y = spd;
                setCurSpriteState(DASH_DOWN);
            }

            // left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                velocity.x = -spd;
                velocity.y = 0;
                setCurSpriteState(DASH_LEFT);
            }

            // right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                velocity.x = spd;
                velocity.y = 0;
                setCurSpriteState(DASH_RIGHT);
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

void Wrestler::setStats(float spd, int str, int wgt, int stm)
{
    speed = spd;
    strength = str;
    weight = wgt;
    stamina = stm;
    acceleration = float(str) / float(wgt) + float(speed);
}

bool Wrestler::isHuman()
{
    return is_human;
}

void Wrestler::setIsHuman(bool val)
{
    is_human = val;
}

void Wrestler::setUpState(bool val)
{
    first_up_state = val;
}

void Wrestler::setDownState(bool val)
{
    first_down_state = val;
}

bool Wrestler::getUpState()
{
    return first_up_state;
}

bool Wrestler::getDownState()
{
    return first_down_state;
}

Wrestler::State Wrestler::getCurrentState()
{
    return current_state;
}

void Wrestler::setCurrentState(State new_state)
{
    current_state = new_state;
}

Wrestler::SpriteState Wrestler::getCurSpriteState()
{
    return sprite_state;
}

void Wrestler::setCurSpriteState(SpriteState new_state)
{
    sprite_state = new_state;
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

void Wrestler::setCharacter(int characterNum)
{
    // acceleration = float(str) / float(wgt); (0.2)
    // setStats(spd str wgt stm);
    switch(characterNum)
    {
        case 1: setStats(0.5, 1, 5, 100); break;
        case 2: setStats(0, 1, 5, 50); break;
    }
}

Wrestler::~Wrestler()
{
    //dtor
}
