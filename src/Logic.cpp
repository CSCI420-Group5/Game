#include "Logic.h"
#include <cmath>
#include <iostream>

void getInputAndMove(Wrestler& sumo, float elapsed_time)
{
    // Get speed as a vector length
    int spd = sqrt((sumo.getXSpd()*sumo.getXSpd())+
              (sumo.getYSpd()*sumo.getYSpd()));
    // Used to keep movement synched
    float move_factor = elapsed_time*spd;
    
    // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sumo.setXSpd(sumo.getXSpd()-move_factor-0.001);
        sumo.setX(sumo.getMovedX());
    }

    // move right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sumo.setXSpd(sumo.getXSpd()+move_factor+0.001);
        sumo.setX(sumo.getMovedX());
    }
    else {
        if (sumo.getXSpd() < 0) {
            sumo.setXSpd(sumo.getXSpd()+move_factor+0.001);
            sumo.setX(sumo.getMovedX());
        }
        else {
            sumo.setXSpd(sumo.getXSpd()-move_factor-0.001);
            sumo.setX(sumo.getMovedX());
        }
    }

    // move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sumo.setYSpd(sumo.getYSpd()-move_factor-0.001);
        sumo.setY(sumo.getMovedY());
    }

    // move down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sumo.setYSpd(sumo.getYSpd()+move_factor+0.001);
        sumo.setY(sumo.getMovedY());
    }
    else {
        if (sumo.getYSpd() < 0) {
            sumo.setYSpd(sumo.getYSpd()+move_factor+0.001);
            sumo.setY(sumo.getMovedY());
        }
        else {
            sumo.setYSpd(sumo.getYSpd()-move_factor-0.001);
            sumo.setY(sumo.getMovedY());
        }
    }
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
    if (player_loc.x < ai_loc.x) {
        ai_sumo.setXSpd(ai_sumo.getXSpd()-move_factor-0.001);
        ai_sumo.setX(ai_sumo.getMovedX());
    }

    // move right
    else if (player_loc.x > ai_loc.x) {
        ai_sumo.setXSpd(ai_sumo.getXSpd()+move_factor+0.001);
        ai_sumo.setX(ai_sumo.getMovedX());
    }

    else {
        if (ai_sumo.getXSpd() < 0) {
            ai_sumo.setXSpd(ai_sumo.getXSpd()+move_factor+0.001);
            ai_sumo.setX(ai_sumo.getMovedX());
        }
        else {
            ai_sumo.setXSpd(ai_sumo.getXSpd()-move_factor-0.001);
            ai_sumo.setX(ai_sumo.getMovedX());
        }
    }

    // move up
    if (player_loc.y < ai_loc.y) {
        ai_sumo.setYSpd(ai_sumo.getYSpd()-move_factor-0.001);
        ai_sumo.setY(ai_sumo.getMovedY());
    }

    // move down
    else if (player_loc.y > ai_loc.y) {
        ai_sumo.setYSpd(ai_sumo.getYSpd()+move_factor+0.001);
        ai_sumo.setY(ai_sumo.getMovedY());
    }

    else {
        if (ai_sumo.getYSpd() < 0) {
            ai_sumo.setYSpd(ai_sumo.getYSpd()+move_factor+0.001);
            ai_sumo.setY(ai_sumo.getMovedY());
        }
        else {
            ai_sumo.setYSpd(ai_sumo.getYSpd()-move_factor-0.001);
            ai_sumo.setY(ai_sumo.getMovedY());
        }
    }
}
