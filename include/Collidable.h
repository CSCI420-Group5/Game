#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "SFML/Graphics.hpp"

class Collidable
{
    public:
    Collidable();

    // method for initializing attributes of the object
    virtual void init(int hit_height, int hit_width, int x, int y);

    // returns new position after moving
    sf::Vector2f getMovedPos();

    void move(float friction);

    // setters & getters
    long int getID() const;

    bool isHuman();
    void setIsHuman(bool val);

    int getHeight() const;
    int getWidth() const;

    void setHeight(int num);
    void setWidth(int num);

    sf::Vector2f getPos() const;
    sf::Vector2f getVelocity() const;

    void setPos(float x, float y);
    void setVelocity(float x, float y);

    // Used for object depth in drawing
    bool operator<(const Collidable &obj) const;

    // virtual with no declaration that child classes can implement
    virtual sf::ConvexShape getPath() {}
    virtual void useGrab() {}
    virtual void useThrow() {}
    virtual void useDash() {}
    virtual int getSpeed() {}
    virtual int getStrength() {}
    virtual int getWeight() {}
    virtual int getStamina() {}
    virtual float getAcceleration() {}
    virtual void setStats() {}
    virtual int getCurrentState() {}
    virtual void setCurrentState() {}

    protected:
    long int id;
    bool is_human;

    // hitbox
    int width;
    int height;

    // position kept as the top-left corner of the hitbox
    sf::Vector2f position;

    // speed and direction vector
    sf::Vector2f velocity;
};

#endif // COLLIDABLE_H

