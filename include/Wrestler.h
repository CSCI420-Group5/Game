#ifndef WRESTLER_H
#define WRESTLER_H
#include "SFML/Graphics.hpp"


class Wrestler
{
    public:
        Wrestler();
        virtual ~Wrestler();

        void init(int hit_length, int hit_width);

        int getMovedX();
        int getMovedY();
        sf::ConvexShape getPath(); //Returns the intermediate shape a wrestles will move through this frame (to avoid clipping)
        void moveWrestler(float friction);

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

        bool isHuman();
        int getCurrentState();

        void setIsHuman(bool val);
        void setCurrentState(int num);

        int getLength();
        int getWidth();

        void setLength(int num);
        void setWidth(int num);

        int getX();
        int getY();
        float getXSpd();
        float getYSpd();

        void setX(int num);
        void setY(int num);
        void setXSpd(float num);
        void setYSpd(float num);

    protected:
    private:
        //attributes
        int speed;
        int strength;
        int weight;
        int stamina;
        float acceleration;

        bool is_human;
        int current_state; //0=normal, 1=grabbing, 2=grabbed, 3=thrown, 4=dashing, 5=falling

        //hitbox
        int length;
        int width;

        //position kept as the top-left corner of the hitbox
        int x;
        int y;
        //Speeds stored as floats so can increase slowly. Should be cast to integers before using.
        float x_spd;
        float y_spd;
};

#endif // WRESTLER_H
