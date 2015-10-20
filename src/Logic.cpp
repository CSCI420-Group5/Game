#include "Logic.h"
#include <cmath>

void moveWrestler(Wrestler& sumo, int dir)
{
    float fin_x = sumo.getMovedX();
    float fin_y = sumo.getMovedY();

    // check borders
    if (fin_x > 0 && fin_x < (800-sumo.getWidth())) {
        // move left
        if (dir == 1) {
            sumo.setXSpd(sumo.getXSpd()-0.1);
            sumo.setX(sumo.getMovedX());
        }

        // move right
        else if (dir == 3) {
            sumo.setXSpd(sumo.getXSpd()+0.1);
            sumo.setX(sumo.getMovedX());
        }

        // if we don't move, slow us down until we stop (friction?)
        else if (dir == 4) {
            if (sumo.getXSpd() < 0) {
                if (sumo.getXSpd() > -0.1) {
                    sumo.setXSpd(0);
                }
                else {
                    sumo.setXSpd(sumo.getXSpd()+0.1);
                    sumo.setX(sumo.getMovedX());
                }
            }
            else {
                if (sumo.getXSpd() < 0.1) {
                    sumo.setXSpd(0);
                }
                else {
                    sumo.setXSpd(sumo.getXSpd()-0.1);
                    sumo.setX(sumo.getMovedX());
                }
            }
        }
    }
    else {
        sumo.setXSpd((-sumo.getXSpd())/2);
    }

    if (fin_y > 0 && fin_y < (600-sumo.getHeight())) {
        // move up
        if (dir == 0) {
            sumo.setYSpd(sumo.getYSpd()-0.1);
            sumo.setY(sumo.getMovedY());
        }

        // move down
        else if (dir == 2) {
            sumo.setYSpd(sumo.getYSpd()+0.1);
            sumo.setY(sumo.getMovedY());
        }

        // if we don't move, slow us down until we stop (friction?)
        else if (dir == 5) {
            if (sumo.getYSpd() < 0) {
                if (sumo.getYSpd() > -0.1){
                    sumo.setYSpd(0);
                }
                else {
                    sumo.setYSpd(sumo.getYSpd()+0.1);
                    sumo.setY(sumo.getMovedY());
                }
            }
            else {
                if (sumo.getYSpd() < 0.1){
                    sumo.setYSpd(0);
                }
                else {
                    sumo.setYSpd(sumo.getYSpd()-0.1);
                    sumo.setY(sumo.getMovedY());
                }
            }
        }
    }
    else {
        sumo.setYSpd((-sumo.getYSpd())/2);
    }
}

void getInputAndMove(Wrestler& sumo)
{

    // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        moveWrestler(sumo, 1);

    // move right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        moveWrestler(sumo, 3);

    // if we don't move, slow us down
    else
        moveWrestler(sumo, 4);

    // move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveWrestler(sumo, 0);

    // move down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        moveWrestler(sumo, 2);

    else
        moveWrestler(sumo, 5);
}

void moveAI(Wrestler& ai_sumo, Wrestler human_sumo)
{

    // get player's and ai's locations
    sf::Vector2f player_loc(human_sumo.getX(), human_sumo.getY());
    sf::Vector2f ai_loc(ai_sumo.getX(), ai_sumo.getY());

    // move left
    if (player_loc.x < ai_loc.x)
        moveWrestler(ai_sumo, 1);

    // move right
    else if (player_loc.x > ai_loc.x)
        moveWrestler(ai_sumo, 3);

    // if we don't move, do friction stuff
    else
        moveWrestler(ai_sumo, 4);

    // move up
    if (player_loc.y < ai_loc.y)
        moveWrestler(ai_sumo, 0);

    // move down
    else if (player_loc.y > ai_loc.y)
        moveWrestler(ai_sumo, 2);

    else
        moveWrestler(ai_sumo, 5);
}

void calcCollision(std::vector<int> ids, std::vector<Wrestler>& wrestlers)
{
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
    }
}
