#include "Logic.h"
#include <cmath>

void moveWrestlers(std::vector<Wrestler> &wrestlers)
{
    for (unsigned int i=0; i<wrestlers.size(); i++) {
        wrestlers[i].moveWrestler(0.1); //Placeholder for friction
    }
}

void setWrestlerSpd(Wrestler& sumo, int dir)
{
/*    float fin_x = sumo.getMovedX();
    float fin_y = sumo.getMovedY();*/
    float acc = 0.2;

    // check borders
/*    if (fin_x > 0 && fin_x < (800-sumo.getWidth())) {*/
        // move left
        if (dir == 1) {
            sumo.setXSpd(sumo.getXSpd()-acc);
        }

        // move right
        else if (dir == 3) {
            sumo.setXSpd(sumo.getXSpd()+acc);
        }

// Friction moved to end of moveWrestler function so as to have an effect when moving too
// Now need to have friction less than acceleration though
/*        // if we don't move, slow us down until we stop (friction?)
        else if (dir == 4) {
            if (sumo.getXSpd() < 0) {
                if (sumo.getXSpd() > -0.1) {
                    sumo.setXSpd(0);
                }
                else {
                    sumo.setXSpd(sumo.getXSpd()+0.1);
                }
            }
            else {
                if (sumo.getXSpd() < 0.1) {
                    sumo.setXSpd(0);
                }
                else {
                    sumo.setXSpd(sumo.getXSpd()-0.1);
                }
            }
        }
    }
    else {
        sumo.setXSpd((-sumo.getXSpd())/2);
    }

    if (fin_y > 0 && fin_y < (600-sumo.getHeight())) {*/
        // move up
        if (dir == 0) {
            sumo.setYSpd(sumo.getYSpd()-acc);
        }

        // move down
        else if (dir == 2) {
            sumo.setYSpd(sumo.getYSpd()+acc);
        }

/*        // if we don't move, slow us down until we stop (friction?)
        else if (dir == 5) {
            if (sumo.getYSpd() < 0) {
                if (sumo.getYSpd() > -0.1){
                    sumo.setYSpd(0);
                }
                else {
                    sumo.setYSpd(sumo.getYSpd()+0.1)
                }
            }
            else {
                if (sumo.getYSpd() < 0.1){
                    sumo.setYSpd(0);
                }
                else {
                    sumo.setYSpd(sumo.getYSpd()-0.1);
                }
            }
        }
    }
    else {
        sumo.setYSpd((-sumo.getYSpd())/2);
    }*/
}

void getInputSetSpd(Wrestler& sumo)
{

    // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        setWrestlerSpd(sumo, 1);

    // move right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        setWrestlerSpd(sumo, 3);

/*    // if we don't move, slow us down
    else
        setWrestlerSpd(sumo, 4);*/

    // move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        setWrestlerSpd(sumo, 0);

    // move down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        setWrestlerSpd(sumo, 2);

/*    else
        setWrestlerSpd(sumo, 5);*/
}

void setAISpd(Wrestler& ai_sumo, Wrestler human_sumo)
{

    // get player's and ai's locations
    sf::Vector2f player_loc(human_sumo.getX(), human_sumo.getY());
    sf::Vector2f ai_loc(ai_sumo.getX(), ai_sumo.getY());

    // move left
    if (player_loc.x < ai_loc.x)
        setWrestlerSpd(ai_sumo, 1);

    // move right
    else if (player_loc.x > ai_loc.x)
        setWrestlerSpd(ai_sumo, 3);

/*    // if we don't move, do friction stuff
    else
        setWrestlerSpd(ai_sumo, 4);*/

    // move up
    if (player_loc.y < ai_loc.y)
        setWrestlerSpd(ai_sumo, 0);

    // move down
    else if (player_loc.y > ai_loc.y)
        setWrestlerSpd(ai_sumo, 2);

/*    else
        setWrestlerSpd(ai_sumo, 5);*/
}

bool calcCollision(std::vector<int> ids, std::vector<Wrestler>& wrestlers, bool have_collided)
{
    if (!have_collided){
        int w1, w2;
        long int tmp_id = ids[0];
        for (unsigned int i=0; i<wrestlers.size(); i++) {
            if (wrestlers[i].getId() == tmp_id)
                w1 = i;
        }
        tmp_id = ids[1];
        for (unsigned int i=0; i<wrestlers.size(); i++) {
            if (wrestlers[i].getId() == tmp_id)
                w2 = i;
        }


        // create rectangle shapes to detect collisions
        sf::RectangleShape
        wrest_box1(sf::Vector2f(wrestlers[w1].getWidth(),wrestlers[w1].getHeight()));
        wrest_box1.setPosition(wrestlers[w1].getX(),wrestlers[w1].getY());

        sf::RectangleShape
        wrest_box2(sf::Vector2f(wrestlers[w2].getWidth(),wrestlers[w2].getWidth()));
        wrest_box2.setPosition(wrestlers[w2].getX(),wrestlers[w2].getY());

        sf::FloatRect w1_bounds = wrest_box1.getGlobalBounds();
        sf::FloatRect w2_bounds = wrest_box2.getGlobalBounds();

        if (w1_bounds.intersects(w2_bounds)) {
            // v1 = (u1(m1-m2)+2m2u2)/m1+m2
            // v2 = (u2(m2-m1)+2m1u1)/m1+m2
            sf::Vector2f
            u1(wrestlers[w1].getXSpd(),wrestlers[w1].getYSpd());

            sf::Vector2f
            u2(wrestlers[w2].getXSpd(),wrestlers[w2].getYSpd());

            // using equal mass temporarily
            sf::Vector2f v1 = u2;
            sf::Vector2f v2 = u1;

            wrestlers[w1].setXSpd(v1.x);
            wrestlers[w1].setYSpd(v1.y);
            wrestlers[w2].setXSpd(v2.x);
            wrestlers[w2].setYSpd(v2.y);

            return true;
        }
    }
    return false;
}
