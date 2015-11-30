#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "SFML/Graphics.hpp"

class Collidable
{
    public:
    Collidable();
    virtual ~Collidable();

    // method for initializing attributes of the object
    virtual void init(int hit_height, int hit_width, int x, int y);

    // returns new position after moving
    sf::Vector2f getMovedPos(int level_w, int level_h);

    void move(float friction, int level_w, int level_h);

    // setters & getters
    std::string getName();
    void setName(std::string actor_name);

    long int getID() const;

    bool isWrestler();
    void setIsWrestler(bool val);

    bool hasProjectile();
    void setHasProjectile(bool val);

    bool offEdge();
    void setOffEdge(bool val);

    int getHeight() const;
    int getWidth() const;

    void setHeight(int num);
    void setWidth(int num);

    float getSpeed();
    float getWeight();

    void setCurrentState(int num);
    int getCurrentState();

    sf::Vector2f getPos() const;
    sf::Vector2f getVelocity() const;

    void setPos(float x, float y);
    void setVelocity(float x, float y, int level_w, int level_h);

    /*// Used for object depth in drawing
    bool operator<(const Collidable &obj) const;*/

    protected:
    std::string name;
    int current_state;
    long int id;
    bool is_wrestler;
    bool has_projectile;

    // used to check if actor is completely off the stage or not
    bool off_edge;

    // hitbox
    int width;
    int height;

    float speed;
    float weight;

    // position kept as the top-left corner of the hitbox
    sf::Vector2f position;

    // speed and direction vector
    sf::Vector2f velocity;
};

#endif // COLLIDABLE_H

