#ifndef LOGIC_H
#define LOGIC_H

#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "Projectile.h"
#include "LocationalMap.h"
#include "set"
#include "string"

void moveActors(std::vector<Collidable*> &actors);

//void getInputSetSpd(Collidable* sumo);
void getInputSetSpd(Collidable* wrestler, LocationalMap& loc_map, std::vector<Collidable*>& actors, std::string ai_code);

void setAISpd(Collidable* ai_sumo, LocationalMap& loc_map, std::vector<Collidable*>& actors);

std::vector<std::set<long int> > calcCollision(LocationalMap& loc_map, std::vector<Collidable*>& actors);

#endif // LOGIC_H
