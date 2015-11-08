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

    bool isWrestler();
    void setIsWrestler(bool val);

    int getHeight() const;
    int getWidth() const;

    void setHeight(int num);
    void setWidth(int num);

    void setCurrentState(int num);
    int getCurrentState();

    sf::Vector2f getPos() const;
    sf::Vector2f getVelocity() const;

    void setPos(float x, float y);
    void setVelocity(float x, float y);

    /*// Used for object depth in drawing
    bool operator<(const Collidable &obj) const;*/

    protected:
    int current_state;
    long int id;
    bool is_wrestler;

    // hitbox
    int width;
    int height;

    // position kept as the top-left corner of the hitbox
    sf::Vector2f position;

    // speed and direction vector
    sf::Vector2f velocity;
};

#endif // COLLIDABLE_H

