#ifndef LOGIC_H
#define LOGIC_H

#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "LocationalMap.h"

void moveWrestlers(std::vector<Wrestler> &wrestlers);

void getInputSetSpd(Wrestler& sumo);

void setAISpd(Wrestler& ai_sumo, Wrestler human_sumo);

bool calcCollision(std::vector<long int> ids, std::vector<Wrestler>& wrestlers, bool have_collided);

#endif // LOGIC_H
