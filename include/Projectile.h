#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

#include "Collidable.h"

class Projectile: public Collidable
{
    public:
        Projectile();
        
        void init(int hit_height, int hit_width, int x, int y);

        sf::Vector2f getBallPos() const;
        sf::Vector2f getBallVel() const;

        void setBallPos(float x, float y);
        void setBallVel(float x, float y);

        bool hasShot();
        void setHasShot(bool val);
        void shootBall();
        void moveBall(float x, float y);

        enum Dir{NORTH = 1, EAST = 2, SOUTH = 3, WEST = 4};
        Dir getDir();
        void setDir(Dir d);
        
    private:
        sf::Vector2f ball_pos;
        sf::Vector2f ball_vel;

        bool has_shot;
        Dir dir;
};

#endif // PROJECTILE_H
