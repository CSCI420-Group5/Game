#include "Logic.h"
#include <cmath>
#include <set>

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

void getInputSetSpd(Collidable* sumo)
{

    // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        setActorSpd(sumo, 1);

    // move right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        setActorSpd(sumo, 3);

    // move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        setActorSpd(sumo, 0);

    // move down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        setActorSpd(sumo, 2);
}

void setAISpd(Collidable* ai_sumo, Collidable* human_sumo)
{

    // get player's and ai's locations
    sf::Vector2f player_pos = human_sumo->getPos();
    sf::Vector2f ai_pos = ai_sumo->getPos();

    // move left
    if (player_pos.x < ai_pos.x)
        setActorSpd(ai_sumo, 1);

    // move right
    else if (player_pos.x > ai_pos.x)
        setActorSpd(ai_sumo, 3);

    // move up
    if (player_pos.y < ai_pos.y)
        setActorSpd(ai_sumo, 0);

    // move down
    else if (player_pos.y > ai_pos.y)
        setActorSpd(ai_sumo, 2);
}

std::vector<std::set<long int> > calcCollision(LocationalMap& loc_map,
std::vector<Collidable*>& actors)
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
                    for (unsigned int w=0; w<actors.size(); w++) {
                        if (actors[w]->getID() == tmp[idi]) {

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
                        wrest_box1(sf::Vector2f(actors[tmp_pos[w1]]->getWidth(),actors[tmp_pos[w1]]->getHeight()));
                        wrest_box1.setPosition(actors[tmp_pos[w1]]->getMovedPos());

                        sf::RectangleShape
                        wrest_box2(sf::Vector2f(actors[tmp_pos[w2]]->getWidth(),actors[tmp_pos[w2]]->getWidth()));
                        wrest_box2.setPosition(actors[tmp_pos[w2]]->getMovedPos());

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
                                u1(actors[tmp_pos[w1]]->getVelocity());
                                sf::Vector2f
                                u2(actors[tmp_pos[w2]]->getVelocity());

                                // using equal mass temporarily
                                float m1 = 10.f;
                                float m2 = 10.f;

                                sf::Vector2f v1 = (u1*(m1-m2)+2.f*m2*u2)/(m1+m2);
                                sf::Vector2f v2 = (u2*(m2-m1)+2.f*m1*u1)/(m1+m2);

                                //Set new speeds
                                actors[tmp_pos[w1]]->setVelocity(v1.x, v1.y);
                                actors[tmp_pos[w2]]->setVelocity(v2.x, v2.y);

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
    return collision_sets;
}
