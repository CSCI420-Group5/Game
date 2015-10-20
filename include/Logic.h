#ifndef LOGIC_H
#define LOGIC_H

#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "LocationalMap.h"

void getInputAndMove(Wrestler& sumo, float elapsed_time);

void moveAI(Wrestler& ai_sumo, Wrestler human_sumo, float elapsed_time);

void calcCollision(std::vector<int> ids, std::vector<Wrestler>& wrestlers);

#endif // LOGIC_H 
