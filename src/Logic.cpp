#include "Logic.h"
#include <cmath>
#include <iostream>

void moveWrestler(Wrestler& sumo, int dir, float move_factor)
{
    // move left
    if (dir == 1) {
        // make sure we stay on the screen
        if (sumo.getX() > 0) {
            sumo.setXSpd(sumo.getXSpd()-move_factor-0.001);
            sumo.setX(sumo.getMovedX());
        }
        else {
            sumo.setX(0);
            sumo.setXSpd(0);
        }
    }

    // move right
    else if (dir == 3) {
        // make sure we stay on the screen
        if (sumo.getX() < (800-sumo.getWidth())) {
            sumo.setXSpd(sumo.getXSpd()+move_factor+0.001);
            sumo.setX(sumo.getMovedX());
        }
        else {
            sumo.setX(800-sumo.getWidth());
            sumo.setXSpd(0);
        }
    }

    // if we don't move, slow us down until we stop (friction?)
    else if (dir == 4) {
        if (sumo.getXSpd() < 0) {
            if (sumo.getX() > 0) {
                sumo.setXSpd(sumo.getXSpd()+move_factor+0.001);
                sumo.setX(sumo.getMovedX());
            }
            else {
                sumo.setX(0);
                sumo.setXSpd(0);
            }
        }
        else {
            if (sumo.getX() < (800-sumo.getWidth())) {
                sumo.setXSpd(sumo.getXSpd()-move_factor-0.001);
                sumo.setX(sumo.getMovedX());
            }
            else {
                sumo.setX(800-sumo.getWidth());
                sumo.setXSpd(0);
            }
        }
    }

    // move up
    else if (dir == 0) {
        if (sumo.getY() > 0) {
            sumo.setYSpd(sumo.getYSpd()-move_factor-0.001);
            sumo.setY(sumo.getMovedY());
        }
        else {
            sumo.setY(0);
            sumo.setYSpd(0);
        }
    }

    // move down
    else if (dir == 2) {
        if (sumo.getY() < (600-sumo.getHeight())) {
            sumo.setYSpd(sumo.getYSpd()+move_factor+0.001);
            sumo.setY(sumo.getMovedY());
        }
        else {
            sumo.setY(600-sumo.getHeight());
            sumo.setYSpd(0);
        }
    }

    else if (dir == 5) {
        if (sumo.getYSpd() < 0) {
            if (sumo.getY() > 0) {
                sumo.setYSpd(sumo.getYSpd()+move_factor+0.001);
                sumo.setY(sumo.getMovedY());
            }
            else {
                sumo.setY(0);
                sumo.setYSpd(0);
            }
        }
        else {
            if (sumo.getY() < (600-sumo.getHeight())) {
                sumo.setYSpd(sumo.getYSpd()-move_factor-0.001);
                sumo.setY(sumo.getMovedY());
            }
            else {
                sumo.setY(600-sumo.getHeight());
                sumo.setYSpd(0);
            }
        }
    }
}

void getInputAndMove(Wrestler& sumo, float elapsed_time)
{
    // Get speed as a vector length
    int spd = sqrt((sumo.getXSpd()*sumo.getXSpd())+
              (sumo.getYSpd()*sumo.getYSpd()));
    // Used to keep movement synched
    float move_factor = elapsed_time*spd;
    
    // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        moveWrestler(sumo, 1, move_factor);

    // move right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        moveWrestler(sumo, 3, move_factor);

    // if we don't move, slow us down
    else
        moveWrestler(sumo, 4, move_factor);

    // move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveWrestler(sumo, 0, move_factor);

    // move down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        moveWrestler(sumo, 2, move_factor);

    else
        moveWrestler(sumo, 5, move_factor);
}

void moveAI(Wrestler& ai_sumo, Wrestler human_sumo, float elapsed_time)
{
    // Get speed as a vector length
    int spd = sqrt((ai_sumo.getXSpd()*ai_sumo.getXSpd())+
              (ai_sumo.getYSpd()*ai_sumo.getYSpd()));
    
    // Used to keep movement synched
    float move_factor = elapsed_time*spd;

    // get player's and ai's locations
    sf::Vector2f player_loc(human_sumo.getX(), human_sumo.getY());
    sf::Vector2f ai_loc(ai_sumo.getX(), ai_sumo.getY());

    // move left
    if (player_loc.x < ai_loc.x)
        moveWrestler(ai_sumo, 1, move_factor);

    // move right
    else if (player_loc.x > ai_loc.x)
        moveWrestler(ai_sumo, 3, move_factor);

    // if we don't move, do friction stuff
    else
        moveWrestler(ai_sumo, 4, move_factor);

    // move up
    if (player_loc.y < ai_loc.y)
        moveWrestler(ai_sumo, 0, move_factor);

    // move down
    else if (player_loc.y > ai_loc.y)
        moveWrestler(ai_sumo, 2, move_factor);

    else
        moveWrestler(ai_sumo, 5, move_factor);
}

void calcCollision(std::vector<int> ids, std::vector<Wrestler>& wrestlers)
{
    int wrestler1, wrestler2;
    int tmp_id = ids[0];
    for (int i=0; i<wrestlers.size(); i++) {
        if (wrestlers[i].getId() == tmp_id)
            wrestler1 = i;
    }
    tmp_id = ids[1];
    for (int i=0; i<wrestlers.size(); i++) {
        if (wrestlers[i].getId() == tmp_id)
            wrestler2 = i;
    }

    // v1 = (u1(m1-m2)+2m2u2)/m1+m2
    // v2 = (u2(m2-m1)+2m1u1)/m1+m2
    sf::Vector2f
    u1(wrestlers[wrestler1].getXSpd(),wrestlers[wrestler1].getYSpd());

    sf::Vector2f
    u2(wrestlers[wrestler2].getXSpd(),wrestlers[wrestler2].getYSpd());

    // using equal mass temporarily
    sf::Vector2f v1 = u2;
    sf::Vector2f v2 = u1;

    wrestlers[wrestler1].setXSpd(v1.x);
    wrestlers[wrestler1].setYSpd(v1.y);
    wrestlers[wrestler2].setXSpd(v2.x);
    wrestlers[wrestler2].setYSpd(v2.y);
}
