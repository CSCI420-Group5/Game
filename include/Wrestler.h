#ifndef WRESTLER_H
#define WRESTLER_H
#include "SFML/Graphics.hpp"

#include "Collidable.h"


class Wrestler: public Collidable
{
    public:
        Wrestler();
        virtual ~Wrestler();

        void init(int hit_height, int hit_width, int x, int y);

        sf::ConvexShape getPath(); //Returns the intermediate shape a wrestler will move through this frame (to avoid clipping)

        void useGrab(Wrestler grabee);
        void useThrow(Wrestler throwee);
        void useDash();

        void increaseStamina();

        //General getters and setters:
        int getSpeed();
        int getStrength();
        int getWeight();
        int getStamina();
        float getAcceleration(); //Currently based on strength/weight

        void setStats(int spd, int str, int wgt, int stm);

        int getCurrentState();

        void setCurrentState(int num);

    protected:
    private:
        //attributes
        int speed;
        int strength;
        int weight;
        int stamina;
        float acceleration;

        int current_state; //0=normal, 1=grabbing, 2=grabbed, 3=thrown, 4=dashing, 5=falling
};

#endif // WRESTLER_H
