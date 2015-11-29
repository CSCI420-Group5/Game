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

        enum Dir{NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};
        Dir getDir();
        void setDir(Dir d);
        
        enum SpriteState{UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};
        SpriteState getState();
        void setState(SpriteState s);

    private:
        sf::Vector2f ball_pos;
        sf::Vector2f ball_vel;

        bool has_shot;
        Dir dir;

        SpriteState state;
};

#endif // PROJECTILE_H
