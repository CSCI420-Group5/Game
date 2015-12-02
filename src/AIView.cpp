#include "AIView.h"
#include "Logic.h"

AIView::AIView()
{
    //ctor
}

bool isSlideOffEdge (Collidable* ai_sumo, LocationalMap& loc_map, std::vector<Collidable*>& actors)
{
    sf::Vector2f old_pos = ai_sumo->getPos();
    sf::Vector2f old_vel = ai_sumo->getVelocity();

    sf::RectangleShape player_box(sf::Vector2f(actors[0]->getWidth(),actors[0]->getHeight()));
    player_box.setPosition(actors[0]->getPos());
    sf::FloatRect player_bounds = player_box.getGlobalBounds();

    sf::RectangleShape ai_box(sf::Vector2f(ai_sumo->getWidth(),ai_sumo->getHeight()));
    ai_box.setPosition(ai_sumo->getPos());
    sf::FloatRect ai_bounds = ai_box.getGlobalBounds();

    while(!(ai_sumo->getVelocity().x == 0 && ai_sumo->getVelocity().y == 0) && !ai_bounds.intersects(player_bounds)){
        ai_sumo->move(loc_map.getFriction(), loc_map.getLevelWidth(), loc_map.getLevelHeight());
        ai_box.setPosition(ai_sumo->getPos());
        ai_bounds = ai_box.getGlobalBounds();
    }

    bool off_edge = loc_map.isActorOffEdge(ai_sumo);

    ai_sumo->setPos(old_pos.x, old_pos.y);
    ai_sumo->setVelocity(old_vel.x, old_vel.y, loc_map.getLevelWidth(), loc_map.getLevelHeight());

    return off_edge;
}

void basicSetSpd(Collidable* ai_sumo, LocationalMap& loc_map,
std::vector<Collidable*>& actors, sf::Sound *sound)
{
    Wrestler* ai_wrest = dynamic_cast<Wrestler*>(ai_sumo);

    //Reverse directions if the ai is sliding off the level's edge on its current path
    if (isSlideOffEdge(ai_wrest, loc_map, actors)){
        // move left if moving right now
        if (ai_wrest->getVelocity().x > 0){
            getInputSetSpd(ai_wrest, loc_map, actors, "left", sound);
        }
        // move right if moving left now
        else if (ai_wrest->getVelocity().x < 0){
            getInputSetSpd(ai_wrest, loc_map, actors, "right", sound);
        }
        // move up if moving down now
        if (ai_wrest->getVelocity().y > 0){
            getInputSetSpd(ai_wrest, loc_map, actors, "up", sound);
        }
        // move down if moving up now
        else if (ai_wrest->getVelocity().y < 0){
            getInputSetSpd(ai_wrest, loc_map, actors, "down", sound);
        }
    }

    else{
        // get player's and ai's locations
        sf::Vector2f player_pos = actors[0]->getPos();
        sf::Vector2f ai_pos = ai_sumo->getPos();

        // move left
        if (player_pos.x < ai_pos.x){
            getInputSetSpd(ai_wrest, loc_map, actors, "left", sound);
        }
        // move right
        else if (player_pos.x > ai_pos.x){
            getInputSetSpd(ai_wrest, loc_map, actors, "right", sound);
        }
        // move up
        if (player_pos.y < ai_pos.y){
            getInputSetSpd(ai_wrest, loc_map, actors, "up", sound);
        }
        // move down
        else if (player_pos.y > ai_pos.y){
            getInputSetSpd(ai_wrest, loc_map, actors, "down", sound);
        }
    }
}

void takeshiSetSpd(Collidable* ai_sumo, LocationalMap& loc_map,
std::vector<Collidable*>& actors, sf::Sound *sound)
{
    //Could implement grabbing and dashing here

    basicSetSpd(ai_sumo, loc_map, actors, sound);
}

void AIView::setAISpd(Collidable* ai_sumo, LocationalMap& loc_map,
std::vector<Collidable*>& actors, sf::Sound *sound)
{
    if (ai_sumo->getName() == "GreyRobot" || ai_sumo->getName() == "GreenRobot" ||
        ai_sumo->getName() == "RedRobot" || ai_sumo->getName() == "BlueRobot"){
        basicSetSpd(ai_sumo, loc_map, actors, sound);
    }
    else if (ai_sumo->getName() == "Takeshi"){
        takeshiSetSpd(ai_sumo, loc_map, actors, sound);
    }
}

AIView::~AIView()
{
    //dtor
}
