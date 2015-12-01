#ifndef LOGIC_H
#define LOGIC_H

#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "Projectile.h"
#include "LocationalMap.h"
#include "Profile.h"
#include "LevelHandler.h"
#include "set"
#include "string"

void moveActors(std::vector<Collidable*> &actors, LocationalMap& loc_map,
Profile& profile, LevelHandler& lev_handler, sf::View sf_view, int
&num_bad_guys);

void getInputSetSpd(Collidable* wrestler, LocationalMap& loc_map, std::vector<Collidable*>& actors, std::string ai_code);

//void setAISpd(Collidable* ai_sumo, LocationalMap& loc_map, std::vector<Collidable*>& actors);

std::vector<std::set<long int> > calcCollision(LocationalMap& loc_map, std::vector<Collidable*>& actors);
void calcProjectileCollision(std::vector<Collidable*>& actors, int level_w, int level_h);

#endif // LOGIC_H
