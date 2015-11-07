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

        void useGrab(Wrestler* grabee);
        void useThrow(Wrestler* throwee);
        void useDash();

        //General getters and setters:
        int getSpeed();
        int getStrength();
        int getWeight();
        int getStamina();
        float getAcceleration(); //Currently based on strength/weight

        void setStats(int spd, int str, int wgt, int stm);

        enum State{NORMAL = 0, GRABBING = 1, GRABBED = 2, THROWN = 3, DASH = 4};
        State getCurrentState();
        void setCurrentState(State new_state);

        int getFrozenFrames();
        void incFrozenFrames();
        void resetFrozenFrames();

    protected:
    private:
        //attributes
        int speed;
        int strength;
        int weight;
        int stamina;
        float acceleration;

        State current_state;
        int frozen_frames;
};

#endif // WRESTLER_H
