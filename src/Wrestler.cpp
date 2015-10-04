#include "Wrestler.h"
#include "SFML/Graphics.hpp"

Wrestler::Wrestler()
{
    //ctor
}

void Wrestler::init(int hit_length, int hit_width)
{
    current_state = 0;

    length = hit_length;
    width = hit_width;

    x_spd = 0;
    y_spd = 0;
}

int Wrestler::getMovedX()
{
    //round off speeds because pixels are whole numbers
    int fin_x = x + int(x_spd - 0.5);

    if(x_spd < 0)
    {
        fin_x = x + int(x_spd + 0.5);
    }
    return fin_x;
}

int Wrestler::getMovedY()
{
    int fin_y = y + int(y_spd - 0.5);

    if(y_spd < 0)
    {
        fin_y = y + int(y_spd + 0.5);
    }
    return fin_y;
}

sf::ConvexShape Wrestler::getPath()
{
    int fin_x = getMovedX();
    int fin_y = getMovedY();

    sf::ConvexShape path;
    path.setPointCount(4);
    path.setPoint(0, sf::Vector2f(fin_x, fin_y));
    path.setPoint(1, sf::Vector2f(x, y));
    path.setPoint(2, sf::Vector2f(x+width, y+height));
    path.setPoint(3, sf::Vector2f(fin_x+width, fin_y+height));

    return path;
}

void Wrestler::moveWrestler(float friction)
{
    x = getMovedX();
    y = getMovedY();

    //If movement is not zero, move closer to it based on friction
    if(x < 0)
    {
        x = x + friction;
    }
    else if(x > 0)
    {
        x = x - friction;
    }
    if(y < 0)
    {
        y = y + friction;
    }
    else if(y > 0)
    {
        y = y - friction;
    }
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
    //Not done
}




//General setters an getters below here:
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

bool Wrestler::isHuman()
{
    return is_human;
}
int Wrestler::getCurrentState()
{
    return current_state;
}
void Wrestler::setIsHuman(bool val)
{
    is_human = val;
}
void Wrestler::setCurrentState(int num)
{
    current_state = num;
}

int Wrestler::getLength()
{
    return length;
}
int Wrestler::getWidth()
{
    return width;
}
void Wrestler::setLength(int num)
{
    length = num;
}
void Wrestler::setWidth(int num)
{
    length = num;
}

int Wrestler::getX()
{
    return x;
}
int Wrestler::getY()
{
    return Y;
}
int Wrestler::getXSpd()
{
    return x_spd;
}
int Wrestler::getYSpd()
{
    return y_spd;
}
void Wrestler::setX(int num)
{
    x = num;
}
void Wrestler::setY(int num)
{
    y = num;
}
void Wrestler::setXSpd(int num)
{
    x_spd = num;
}
void Wrestler::setYSpd(int num)
{
    y_spd = num;
}

Wrestler::~Wrestler()
{
    //dtor
}
