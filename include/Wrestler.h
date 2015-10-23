#ifndef WRESTLER_H
#define WRESTLER_H
#include "SFML/Graphics.hpp"


class Wrestler
{
    public:
        Wrestler();
        virtual ~Wrestler();

        void init(int hit_length, int hit_width, int x_pos, int y_pos);

        long int getId();

        float getMovedX();
        float getMovedY();
        sf::ConvexShape getPath(); //Returns the intermediate shape a wrestler will move through this frame (to avoid clipping)
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

        int getHeight();
        int getWidth();

        void setHeight(int num);
        void setWidth(int num);

        int getX() const;
        int getY() const;
        float getXSpd();
        float getYSpd();

        void setX(float num);
        void setY(float num);
        void setXSpd(float num);
        void setYSpd(float num);

        bool operator<(const Wrestler &wrest) const;

    protected:
    private:
        long int id;

        //attributes
        int speed;
        int strength;
        int weight;
        int stamina;
        float acceleration;

        bool is_human;
        int current_state; //0=normal, 1=grabbing, 2=grabbed, 3=thrown, 4=dashing, 5=falling

        //hitbox, width is x direction and height is y direction
        int width;
        int height;

        //position kept as the top-left corner of the hitbox
        int x;
        int y;
        //Speeds stored as floats so can increase slowly. Should be cast to integers before using.
        float x_spd;
        float y_spd;
};

#endif // WRESTLER_H
