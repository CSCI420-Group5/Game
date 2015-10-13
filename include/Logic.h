#ifndef LOGIC_H
#define LOGIC_H

#include "SFML/Graphics.hpp"
#include "Wrestler.h"

void getInputAndMove(Wrestler& sumo, sf::Time time);

void moveAI(Wrestler& ai_sumo, Wrestler human_sumo, sf::Time time);

// detectCollision()
// calcCollision()

#endif // LOGIC_H 
