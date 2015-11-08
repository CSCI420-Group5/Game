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

        void increaseStamina();

        //General getters and setters:
        int getSpeed();
        int getStrength();
        int getWeight();
        int getStamina();
        float getAcceleration(); //Currently based on strength/weight

        void setStats(int spd, int str, int wgt, int stm);
        bool isHuman();
        void setIsHuman(bool val);

        void setUpState(bool val);
        void setDownState(bool val);

        bool getUpState();
        bool getDownState();
        enum State{NORMAL = 0, GRABBING = 1, GRABBED = 2, THROWN = 3, DASH = 4};

        enum SpriteState{STAND_RIGHT = 0, STAND_LEFT = 1, STAND_UP = 2,
        STAND_DOWN = 3, RUN_RIGHT1 = 4, RUN_RIGHT2 = 5, RUN_LEFT1 = 6,
        RUN_LEFT2 = 7, RUN_UP1 = 8, RUN_UP2 = 9, RUN_DOWN1 = 10, RUN_DOWN2 = 11,
        DASH_RIGHT = 12, DASH_LEFT = 13, DASH_UP = 14, DASH_DOWN = 15};

        State getCurrentState();
        void setCurrentState(State new_state);

        SpriteState getCurSpriteState();
        void setCurSpriteState(SpriteState new_state);

        int getFrozenFrames();
        void incFrozenFrames();
        void resetFrozenFrames();

        long int getIDOfGrabbed();
        void setIDOfGrabbed(long int id);

    protected:
    private:
        //attributes
        int speed;
        int strength;
        int weight;
        int stamina;
        float acceleration;

        bool is_human;

        // used for properly switching sprite states
        bool first_up_state;
        bool first_down_state;

        State current_state;
        SpriteState sprite_state;
        int frozen_frames;

        long int id_of_grabbed;
};

#endif // WRESTLER_H
