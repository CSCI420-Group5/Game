#include "AIView.h"
#include "Logic.h"

AIView::AIView()
{
    //ctor
}

bool isSlideOffEdge (Collidable* ai_sumo, LocationalMap& loc_map)
{
    sf::Vector2f old_pos = ai_sumo->getPos();
    sf::Vector2f old_vel = ai_sumo->getVelocity();

    while(!(ai_sumo->getVelocity().x == 0 && ai_sumo->getVelocity().y == 0)){
        ai_sumo->move(loc_map.getFriction(), loc_map.getLevelWidth(), loc_map.getLevelHeight());
    }

    bool off_edge = loc_map.isActorOffEdge(ai_sumo);

    ai_sumo->setPos(old_pos.x, old_pos.y);
    ai_sumo->setVelocity(old_vel.x, old_vel.y, loc_map.getLevelWidth(), loc_map.getLevelHeight());

    return off_edge;
}

void basicSetSpd(Collidable* ai_sumo, LocationalMap& loc_map, std::vector<Collidable*>& actors)
{
    Wrestler* ai_wrest = dynamic_cast<Wrestler*>(ai_sumo);

    //Reverse directions if the ai is sliding off the level's edge on its current path
    if (isSlideOffEdge(ai_wrest, loc_map)){
        // move left if moving right now
        if (ai_wrest->getVelocity().x > 0){
            getInputSetSpd(ai_wrest, loc_map, actors, "left");
        }
        // move right if moving left now
        else if (ai_wrest->getVelocity().x < 0){
            getInputSetSpd(ai_wrest, loc_map, actors, "right");
        }
        // move up if moving down now
        if (ai_wrest->getVelocity().y > 0){
            getInputSetSpd(ai_wrest, loc_map, actors, "up");
        }
        // move down if moving up now
        else if (ai_wrest->getVelocity().y < 0){
            getInputSetSpd(ai_wrest, loc_map, actors, "down");
        }
    }

    else{
        // get player's and ai's locations
        sf::Vector2f player_pos = actors[0]->getPos();
        sf::Vector2f ai_pos = ai_sumo->getPos();

        // move left
        if (player_pos.x < ai_pos.x){
            getInputSetSpd(ai_wrest, loc_map, actors, "left");
        }
        // move right
        else if (player_pos.x > ai_pos.x){
            getInputSetSpd(ai_wrest, loc_map, actors, "right");
        }
        // move up
        if (player_pos.y < ai_pos.y){
            getInputSetSpd(ai_wrest, loc_map, actors, "up");
        }
        // move down
        else if (player_pos.y > ai_pos.y){
            getInputSetSpd(ai_wrest, loc_map, actors, "down");
        }
    }
}

void fumioSetSpd(Collidable* ai_sumo, LocationalMap& loc_map, std::vector<Collidable*>& actors)
{
    //Could implement grabbing and dashing here

    basicSetSpd(ai_sumo, loc_map, actors);
}

void AIView::setAISpd(Collidable* ai_sumo, LocationalMap& loc_map, std::vector<Collidable*>& actors)
{
    if (ai_sumo->getName() == "GreyRobot" || ai_sumo->getName() == "GreenRobot" ||
        ai_sumo->getName() == "RedRobot" || ai_sumo->getName() == "BlueRobot"){
        basicSetSpd(ai_sumo, loc_map, actors);
    }
    else if (ai_sumo->getName() == "Takeshi"){
        fumioSetSpd(ai_sumo, loc_map, actors);
    }
}

AIView::~AIView()
{
    //dtor
}
