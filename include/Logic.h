#ifndef LOGIC_H
#define LOGIC_H

#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "LocationalMap.h"
#include "set"

void moveActors(std::vector<Collidable*> &actors);

//void getInputSetSpd(Collidable* sumo);
void getInputSetSpd(LocationalMap& loc_map, std::vector<Collidable*>& actors);

void setAISpd(Collidable* ai_sumo, Collidable* human_sumo);

std::vector<std::set<long int> > calcCollision(LocationalMap& loc_map, std::vector<Collidable*>& actors);

#endif // LOGIC_H
