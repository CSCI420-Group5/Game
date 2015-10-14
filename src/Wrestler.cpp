#include "Wrestler.h"
#include "SFML/Graphics.hpp"

Wrestler::Wrestler()
{
    //ctor
}

void Wrestler::init(int hit_height, int hit_width, int x_pos, int y_pos)
{
    //Maybe should be a more unique id
    id = reinterpret_cast<long int>(&id);

    current_state = 0;

    height = hit_height;
    width = hit_width;

    x = x_pos;
    y = y_pos;

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
    if(x_spd < 0)
    {
        x_spd = x_spd + friction;
    }
    else if(x > 0)
    {
        x_spd = x_spd - friction;
    }
    if(y_spd < 0)
    {
        y_spd = y_spd + friction;
    }
    else if(y_spd > 0)
    {
        y_spd = y_spd - friction;
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
long int Wrestler::getId()
{
    return id;
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

int Wrestler::getHeight()
{
    return height;
}
int Wrestler::getWidth()
{
    return width;
}
void Wrestler::setHeight(int num)
{
    height = num;
}
void Wrestler::setWidth(int num)
{
    width = num;
}

int Wrestler::getX() const
{
    return x;
}
int Wrestler::getY() const
{
    return y;
}
float Wrestler::getXSpd()
{
    return x_spd;
}
float Wrestler::getYSpd()
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
void Wrestler::setXSpd(float num)
{
    x_spd = num;
}
void Wrestler::setYSpd(float num)
{
    y_spd = num;
}

bool Wrestler::operator < (const Wrestler &wrest) const
{
  return (y < wrest.getY());
}

Wrestler::~Wrestler()
{
    //dtor
}
