#include "Logic.h"
#include <cmath>

// TODO how to use Wrestler::moveWresler() method to update location?
void getInputAndMove(Wrestler& sumo, sf::Time time)
{
    // Get speed as a vector length
    int spd = sqrt((sumo.getXSpd()*sumo.getXSpd())+
              (sumo.getYSpd()*sumo.getYSpd()));
    // used to keep movement synched 
    float move_factor = time.asSeconds()*spd;
    
    // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sumo.setXSpd(-move_factor-10);
    }

    // move right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sumo.setXSpd(move_factor+10);
    }

    // move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sumo.setYSpd(-move_factor-10);
    }

    // move down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sumo.setYSpd(move_factor+10);
    }
}

void moveAI(Wrestler& ai_sumo, Wrestler human_sumo, sf::Time time)
{
    // Get speed as a vector length
    int spd = sqrt((ai_sumo.getXSpd()*ai_sumo.getXSpd())+
              (ai_sumo.getYSpd()*ai_sumo.getYSpd()));
    // used to keep movement synched 
    float move_factor = time.asSeconds()*spd;
    
    // get player's and ai's locations
    sf::Vector2f player_loc(human_sumo.getX(), human_sumo.getY());
    sf::Vector2f ai_loc(ai_sumo.getX(), ai_sumo.getY());

    // move left
    if (player_loc.x < ai_loc.x) {
        ai_sumo.setXSpd(-move_factor-10);
    }

    // move right
    else if (player_loc.x > ai_loc.x) {
        ai_sumo.setXSpd(move_factor+10);
    }

    // move up
    if (player_loc.y < ai_loc.y) {
        ai_sumo.setYSpd(-move_factor-10);
    }

    // move down
    if (player_loc.y > ai_loc.y) {
        ai_sumo.setYSpd(move_factor+10);
    }
}
