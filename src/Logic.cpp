#include "Logic.h"
#include <cmath>
#include <set>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cmath>

Collidable* getActorById(long int id, std::vector<Collidable*>& actors)
{
    for (unsigned int w=0; w<actors.size(); w++) {
        if (actors[w]->getID() == id) {
            return actors[w];
        }
    }
    throw std::invalid_argument("No such ID in actor vector");
}

float findCurrentDistance(Wrestler* wrest1, Wrestler* wrest2)
{
    //This function finds the distance between two wrestlers for the current frame
    sf::Vector2f w1_center(wrest1->getPos().x + wrest1->getWidth()/2, wrest1->getPos().y + wrest1->getHeight()/2);
    sf::Vector2f w2_center(wrest2->getPos().x + wrest2->getWidth()/2, wrest2->getPos().y + wrest2->getHeight()/2);
    sf::Vector2f diff = w1_center - w2_center;

    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

Wrestler* findNearestCollidingWrestler(LocationalMap& loc_map, std::vector<Collidable*>& actors, Wrestler* wrest1)
{
    //This function will find the nearest of all objects colliding with wrest1 for the current frame
    std::set<Wrestler*> collision_set;
    std::vector<long int> tmp;
    std::vector<Wrestler*> sel_wrests;

    for (int i=0; i<loc_map.getRows(); i++) {
        for (int j=0; j<loc_map.getCols(); j++) {

            tmp = loc_map.getCell(i, j);

            // if there's wrestlers colliding with the one we set (Need to check if the vector contains wrest1)
            if (tmp.size() >= 2 && std::find(tmp.begin(), tmp.end(), wrest1->getID()) != tmp.end()) {

                //Find the wrestlers in the main list from their ids and choose those that are not the one we set and that are wrestlers
                for (unsigned int idi=0; idi<tmp.size(); idi++){
                    if (tmp[idi] != wrest1->getID()){

                        Wrestler* other = dynamic_cast<Wrestler*>(getActorById(tmp[idi], actors));
                        if (other){
                            sel_wrests.push_back(other);
                        }
                    }
                }

                // create rectangle shapes to detect collisions from where the object is
                sf::RectangleShape
                wrest_box1(sf::Vector2f(wrest1->getWidth(),wrest1->getHeight()));
                wrest_box1.setPosition(wrest1->getPos());
                sf::FloatRect w1_bounds = wrest_box1.getGlobalBounds();

                //Have to compare everything to our wrestler
                for (unsigned int w=0; w<sel_wrests.size(); w++){

                    sf::RectangleShape
                    wrest_box2(sf::Vector2f(sel_wrests[w]->getWidth(),sel_wrests[w]->getWidth()));
                    wrest_box2.setPosition(sel_wrests[w]->getPos());

                    sf::FloatRect w2_bounds = wrest_box2.getGlobalBounds();

                    //Check if the bounding boxes intersect
                    if (w1_bounds.intersects(w2_bounds)) {
                        collision_set.insert(sel_wrests[w]);
                    }
                }
            }
            tmp.clear();
            sel_wrests.clear();
        }
    }
    //Now need to find the nearest of Collising wrestlers
    Wrestler* nearest = NULL;
    float nearest_dist = std::numeric_limits<float>::max();

    std::set<Wrestler*>::iterator it;
    for (it = collision_set.begin(); it != collision_set.end(); ++it){
        float dist = findCurrentDistance(wrest1, *it);
        if (dist < nearest_dist){
            nearest = *it;
            nearest_dist = dist;
        }
    }
    return nearest;
}

std::vector<std::set<long int> > findFutureCollisions(LocationalMap& loc_map,
                                                      std::vector<Collidable*>& actors)
{
    std::vector<std::set<long int> > collision_sets;
    std::vector<long int> tmp;
    std::vector<Collidable*> sel_actors;
    bool in_set = false;

    for (int i=0; i<loc_map.getRows(); i++) {
        for (int j=0; j<loc_map.getCols(); j++) {

            tmp = loc_map.getCell(i, j);

            // if there's possibly colliding items
            if (tmp.size() >= 2) {

                //Find the wrestlers in the main list from their ids and put the location in main list in vector parallel to tmp
                for (unsigned int idi=0; idi<tmp.size(); idi++){
                    sel_actors.push_back(getActorById(tmp[idi], actors));
                }

                //Have to compare everything in the cell to each other, but omit same object and alternate permutations
                for (unsigned int w1=0; w1<sel_actors.size(); w1++){
                    for (unsigned int w2=w1+1; w2<sel_actors.size(); w2++){

                        // create rectangle shapes to detect collisions from where the object will be next frame
                        sf::RectangleShape
                        wrest_box1(sf::Vector2f(sel_actors[w1]->getWidth(),sel_actors[w1]->getHeight()));
                        wrest_box1.setPosition(sel_actors[w1]->getMovedPos());

                        sf::RectangleShape
                        wrest_box2(sf::Vector2f(sel_actors[w2]->getWidth(),sel_actors[w2]->getWidth()));
                        wrest_box2.setPosition(sel_actors[w2]->getMovedPos());

                        sf::FloatRect w1_bounds = wrest_box1.getGlobalBounds();
                        sf::FloatRect w2_bounds = wrest_box2.getGlobalBounds();

                        //Check if the bounding boxes intersect
                        if (w1_bounds.intersects(w2_bounds)) {

                            //Have to see if the pair is already in a set
                            for (unsigned int cs=0; cs<collision_sets.size(); cs++){
                                if ((collision_sets[cs].find(tmp[w1]) != collision_sets[cs].end()) &&
                                    (collision_sets[cs].find(tmp[w2]) != collision_sets[cs].end())){

                                    in_set = true;
                                    break;
                                }
                            }

                            //insert ids into a new set if not already in a set
                            if (!in_set){

                                //Insert ids for no more collisions this iteration
                                std::set<long int> new_set;
                                new_set.insert(tmp[w1]);
                                new_set.insert(tmp[w2]);

                                collision_sets.push_back(new_set);
                                in_set = false;

                                //std::cout << "Collision between: Wrestler " << tmp_pos[w1] << " and Wrestler " << tmp_pos[w2] << std::endl;
                            }
                        }
                    }
                }
            }
            tmp.clear();
            sel_actors.clear();
        }
    }
    return collision_sets;
}

void moveActors(std::vector<Collidable*> &actors)
{
    for (unsigned int i=0; i<actors.size(); i++) {
        actors[i]->move(0.1); //Placeholder for friction
    }
}

void setActorSpd(Collidable* actor, int dir)
{
    float acc = 0.2;
        // move left
        if (dir == 1) {
            actor->setVelocity(actor->getVelocity().x-acc, actor->getVelocity().y);
        }

        // move right
        else if (dir == 3) {
            actor->setVelocity(actor->getVelocity().x+acc, actor->getVelocity().y);
        }
        // move up
        if (dir == 0) {
            actor->setVelocity(actor->getVelocity().x, actor->getVelocity().y-acc);
        }

        // move down
        else if (dir == 2) {
            actor->setVelocity(actor->getVelocity().x, actor->getVelocity().y+acc);
        }
}

void getInputSetSpd(LocationalMap& loc_map, std::vector<Collidable*>& actors)
//void getInputSetSpd(Wrestler* sumo)
{
    Wrestler *w = dynamic_cast<Wrestler*>(actors[0]);

    // increase stamina 
    w->increaseStamina(); 

    //Need to unfreeze the wrestler if enough frames (time) have passed for each special state
    if (w->getCurrentState() == Wrestler::DASH && w->getFrozenFrames() >= 45){
        w->setCurrentState(Wrestler::NORMAL);
    }

    if ((w->getCurrentState() == Wrestler::GRABBING || w->getCurrentState() == Wrestler::GRABBED) && w->getFrozenFrames() >= 240){
        w->setCurrentState(Wrestler::NORMAL);
    }

    //Can't move, dash, or grab if in a special state
    if (w->getCurrentState() == Wrestler::NORMAL){
        // dash
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
            w->useDash();
        }

        // grab
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
            //How far away the wrestler can grab
            int range = 20;

            int w_height = w->getHeight();
            int w_width = w->getWidth();
            sf::Vector2f w_pos = w->getPos();

            //Make the wrestler bigger so can grab objects that aren't immediately next to it
            w->setHeight(w_height + range+2);
            w->setWidth(w_width + range*2);
            w->setPos(w_pos.x - range, w_pos.y - range);

            //Check the current locations to find intersections
            loc_map.addCurrent(actors);

            Wrestler* other = findNearestCollidingWrestler(loc_map, actors, w);

            loc_map.clearCells();

            //Return wrestler to its initial size
            w->setHeight(w_height);
            w->setWidth(w_width);
            w->setPos(w_pos.x, w_pos.y);

            if (other){
                w->useGrab(other);
            }
        }

        // move left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            setActorSpd(w, 1);
        }

        // move right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            setActorSpd(w, 3);
        }

        // move up
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            setActorSpd(w, 0);
        }

        // move down
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            setActorSpd(w, 2);
        }
    }

    //Can only use throws if grabbing
    else if (w->getCurrentState() == Wrestler::GRABBING){
     //WRITE
    }

    w->incFrozenFrames();
}

void setAISpd(Collidable* ai_sumo, Collidable* human_sumo)
{

    // get player's and ai's locations
    sf::Vector2f player_pos = human_sumo->getPos();
    sf::Vector2f ai_pos = ai_sumo->getPos();

    // move left
    if (player_pos.x < ai_pos.x){
        setActorSpd(ai_sumo, 1);
    }

    // move right
    else if (player_pos.x > ai_pos.x){
        setActorSpd(ai_sumo, 3);
    }

    // move up
    if (player_pos.y < ai_pos.y){
        setActorSpd(ai_sumo, 0);
    }

    // move down
    else if (player_pos.y > ai_pos.y){
        setActorSpd(ai_sumo, 2);
    }
}

std::vector<std::set<long int> > calcCollision(LocationalMap& loc_map,
                                               std::vector<Collidable*>& actors)
{
    std::vector<std::set<long int> > collision_sets = findFutureCollisions(loc_map, actors);
    std::vector<Collidable*> sel_actors;

    for(unsigned int i = 0; i < collision_sets.size(); i++){

        //Find the wrestlers according to their IDs
        std::set<long int>::iterator it;
        for (it = collision_sets[i].begin(); it != collision_sets[i].end(); ++it){
            sel_actors.push_back(getActorById(*it, actors));
        }

        //Calculate collision
        // v1 = (u1(m1-m2)+2m2u2)/m1+m2
        // v2 = (u2(m2-m1)+2m1u1)/m1+m2
        sf::Vector2f
        u1(sel_actors[0]->getVelocity());
        sf::Vector2f
        u2(sel_actors[1]->getVelocity());

        // using equal mass temporarily
        float m1 = 10.f;
        float m2 = 10.f;

        sf::Vector2f v1 = (u1*(m1-m2)+2.f*m2*u2)/(m1+m2);
        sf::Vector2f v2 = (u2*(m2-m1)+2.f*m1*u1)/(m1+m2);

        //Set new speeds
        sel_actors[0]->setVelocity(v1.x, v1.y);
        sel_actors[1]->setVelocity(v2.x, v2.y);

        //If either of these objects are wrestlers, return its state to NORMAL
        Wrestler* first = dynamic_cast<Wrestler*>(sel_actors[0]);
        Wrestler* second = dynamic_cast<Wrestler*>(sel_actors[1]);
        if (first && first->getCurrentState() != Wrestler::NORMAL){
            first->setCurrentState(Wrestler::NORMAL);
        }
        if (second && second->getCurrentState() != Wrestler::NORMAL){
            second->setCurrentState(Wrestler::NORMAL);
        }

        sel_actors.clear();
    }

    return collision_sets;
}
