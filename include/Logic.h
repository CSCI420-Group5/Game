#ifndef LOGIC_H
#define LOGIC_H

#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "LocationalMap.h"

void moveWrestlers(std::vector<Wrestler> &wrestlers);

void getInputSetSpd(Wrestler& sumo);

void setAISpd(Wrestler& ai_sumo, Wrestler human_sumo);

void calcCollision(LocationalMap& loc_map, std::vector<Wrestler>& wrestlers);

#endif // LOGIC_H
