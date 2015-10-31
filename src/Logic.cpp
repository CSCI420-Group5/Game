#include "Logic.h"
#include <cmath>
#include <iostream>
#include <set>

void moveWrestlers(std::vector<Wrestler> &wrestlers)
{
    for (unsigned int i=0; i<wrestlers.size(); i++) {
        wrestlers[i].moveWrestler(0.1); //Placeholder for friction
    }
}

void setWrestlerSpd(Wrestler& sumo, int dir)
{
    float acc = 0.2;
        // move left
        if (dir == 1) {
            sumo.setXSpd(sumo.getXSpd()-acc);
        }

        // move right
        else if (dir == 3) {
            sumo.setXSpd(sumo.getXSpd()+acc);
        }
        // move up
        if (dir == 0) {
            sumo.setYSpd(sumo.getYSpd()-acc);
        }

        // move down
        else if (dir == 2) {
            sumo.setYSpd(sumo.getYSpd()+acc);
        }
}

void getInputSetSpd(Wrestler& sumo)
{

    // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        setWrestlerSpd(sumo, 1);

    // move right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        setWrestlerSpd(sumo, 3);

    // move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        setWrestlerSpd(sumo, 0);

    // move down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        setWrestlerSpd(sumo, 2);
}

void setAISpd(Wrestler& ai_sumo, Wrestler human_sumo)
{

    // get player's and ai's locations
    sf::Vector2f player_loc(human_sumo.getX(), human_sumo.getY());
    sf::Vector2f ai_loc(ai_sumo.getX(), ai_sumo.getY());

    // move left
    if (player_loc.x < ai_loc.x)
        setWrestlerSpd(ai_sumo, 1);

    // move right
    else if (player_loc.x > ai_loc.x)
        setWrestlerSpd(ai_sumo, 3);

    // move up
    if (player_loc.y < ai_loc.y)
        setWrestlerSpd(ai_sumo, 0);

    // move down
    else if (player_loc.y > ai_loc.y)
        setWrestlerSpd(ai_sumo, 2);
}

void calcCollision(LocationalMap& loc_map, std::vector<Wrestler>& wrestlers)
{
    std::vector<std::set<long int> > collision_sets;
    std::vector<long int> tmp;
    std::vector<int> tmp_pos;
    bool in_set = false;

    for (int i=0; i<loc_map.getRows(); i++) {
        for (int j=0; j<loc_map.getCols(); j++) {

            tmp = loc_map.getCell(i, j);

            // if there's possibly colliding items
            if (tmp.size() >= 2) {

                //Find the wrestlers in the main list from their ids and put the location in main list in vector parallel to tmp
                for (unsigned int idi=0; idi<tmp.size(); idi++){
                    for (unsigned int w=0; w<wrestlers.size(); w++) {
                        if (wrestlers[w].getId() == tmp[idi]) {

                            tmp_pos.push_back(w);
                            break;
                        }
                    }
                }

                //Have to compare everything in the cell to each other, but omit same object and alternate permutations
                for (unsigned int w1=0; w1<tmp.size(); w1++){
                    for (unsigned int w2=w1+1; w2<tmp.size(); w2++){

                        // create rectangle shapes to detect collisions from where the object will be next frame
                        sf::RectangleShape
                        wrest_box1(sf::Vector2f(wrestlers[tmp_pos[w1]].getWidth(),wrestlers[tmp_pos[w1]].getHeight()));
                        wrest_box1.setPosition(wrestlers[tmp_pos[w1]].getMovedX(),wrestlers[tmp_pos[w1]].getMovedY());

                        sf::RectangleShape
                        wrest_box2(sf::Vector2f(wrestlers[tmp_pos[w2]].getWidth(),wrestlers[tmp_pos[w2]].getWidth()));
                        wrest_box2.setPosition(wrestlers[tmp_pos[w2]].getMovedX(),wrestlers[tmp_pos[w2]].getMovedY());

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

                            //Do collision and insert ids into a new set if not already in a set
                            if (!in_set){
                                //Calculate collision
                                // v1 = (u1(m1-m2)+2m2u2)/m1+m2
                                // v2 = (u2(m2-m1)+2m1u1)/m1+m2
                                sf::Vector2f
                                u1(wrestlers[tmp_pos[w1]].getXSpd(),wrestlers[tmp_pos[w1]].getYSpd());

                                sf::Vector2f
                                u2(wrestlers[tmp_pos[w2]].getXSpd(),wrestlers[tmp_pos[w2]].getYSpd());

                                //Set positions so they aren't overlapping
                                int mid_x = (wrestlers[tmp_pos[w1]].getMovedX() + wrestlers[tmp_pos[w2]].getMovedX() + wrestlers[tmp_pos[w2]].getWidth()) / 2;
                                int mid_y = (wrestlers[tmp_pos[w1]].getMovedY() + wrestlers[tmp_pos[w2]].getMovedY() + wrestlers[tmp_pos[w2]].getHeight()) / 2;

                                //Don't allow the wrestlers to move outside of the collision path
                                //Set the mid position to the edge of the one being hit
                                if (u1.x >= 0 && u2.x >= 0){
                                    if (u1.x > u2.x){
                                        mid_x = wrestlers[tmp_pos[w2]].getMovedX();
                                    }
                                    else{
                                        mid_x = wrestlers[tmp_pos[w1]].getMovedX();
                                    }
                                }
                                else if(u1.x <= 0 && u2.x <= 0){
                                    if (u1.x < u2.x){
                                        mid_x = wrestlers[tmp_pos[w2]].getMovedX() + wrestlers[tmp_pos[w2]].getWidth();
                                    }
                                    else{
                                        mid_x = wrestlers[tmp_pos[w1]].getMovedX() + wrestlers[tmp_pos[w1]].getWidth();
                                    }
                                }
                                if (u1.y >= 0 && u2.y >= 0){
                                    if (u1.y > u2.y){
                                        mid_y = wrestlers[tmp_pos[w2]].getMovedY();
                                    }
                                    else{
                                        mid_y = wrestlers[tmp_pos[w1]].getMovedY();
                                    }
                                }
                                else if(u1.y <= 0 && u2.y <= 0){
                                    if (u1.y < u2.y){
                                        mid_y = wrestlers[tmp_pos[w2]].getMovedY() + wrestlers[tmp_pos[w2]].getHeight();
                                    }
                                    else{
                                        mid_y = wrestlers[tmp_pos[w1]].getMovedY() + wrestlers[tmp_pos[w1]].getHeight();
                                    }
                                }

                                //Readjust position on x-axis if mostly colliding on x or y-axis if mostly colliding on y. Both if same.
                                if (std::abs(wrestlers[tmp_pos[w1]].getX() - wrestlers[tmp_pos[w2]].getX()) >=
                                    std::abs(wrestlers[tmp_pos[w1]].getY() - wrestlers[tmp_pos[w2]].getY())){

                                    //w1 is starts on the left
                                    if (wrestlers[tmp_pos[w1]].getX() < wrestlers[tmp_pos[w2]].getX()){
                                        wrestlers[tmp_pos[w1]].setX(mid_x - wrestlers[tmp_pos[w1]].getWidth());
                                        wrestlers[tmp_pos[w2]].setX(mid_x);
                                    }
                                    //w1 is starts on the right
                                    else if (wrestlers[tmp_pos[w1]].getX() > wrestlers[tmp_pos[w2]].getX()){
                                        wrestlers[tmp_pos[w1]].setX(mid_x);
                                        wrestlers[tmp_pos[w2]].setX(mid_x - wrestlers[tmp_pos[w2]].getWidth());
                                    }
                                }
                                if (std::abs(wrestlers[tmp_pos[w1]].getY() - wrestlers[tmp_pos[w2]].getY()) >=
                                    std::abs(wrestlers[tmp_pos[w1]].getX() - wrestlers[tmp_pos[w2]].getX())){

                                    //w1 is starts on the top
                                    if (wrestlers[tmp_pos[w1]].getY() < wrestlers[tmp_pos[w2]].getY()){
                                        wrestlers[tmp_pos[w1]].setY(mid_y - wrestlers[tmp_pos[w1]].getHeight());
                                        wrestlers[tmp_pos[w2]].setY(mid_y);
                                    }
                                    //w1 is starts on the bottom
                                    else if (wrestlers[tmp_pos[w1]].getY() > wrestlers[tmp_pos[w2]].getY()){
                                        wrestlers[tmp_pos[w1]].setY(mid_y);
                                        wrestlers[tmp_pos[w2]].setY(mid_y - wrestlers[tmp_pos[w2]].getHeight());
                                    }
                                }

                                // using equal mass temporarily
                                float m1 = 10.f;
                                float m2 = 10.f;

                                sf::Vector2f v1 = (u1*(m1-m2)+2.f*m2*u2)/(m1+m2);
                                sf::Vector2f v2 = (u2*(m2-m1)+2.f*m1*u1)/(m1+m2);

                                //Set new speeds
                                wrestlers[tmp_pos[w1]].setXSpd(v1.x);
                                wrestlers[tmp_pos[w1]].setYSpd(v1.y);
                                wrestlers[tmp_pos[w2]].setXSpd(v2.x);
                                wrestlers[tmp_pos[w2]].setYSpd(v2.y);

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
            tmp_pos.clear();
        }
    }
}
