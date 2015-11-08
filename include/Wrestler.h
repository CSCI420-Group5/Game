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

        //General getters and setters:
        int getSpeed();
        int getStrength();
        int getWeight();
        int getStamina();
        float getAcceleration(); //Currently based on strength/weight

        void setStats(int spd, int str, int wgt, int stm);

        void setUpState(bool val);
        void setDownState(bool val);

        bool getUpState();
        bool getDownState();

    protected:
    private:
        //attributes
        int speed;
        int strength;
        int weight;
        int stamina;
        float acceleration;

        // used for properly switching sprite states
        bool first_up_state;
        bool first_down_state;

};

#endif // WRESTLER_H
