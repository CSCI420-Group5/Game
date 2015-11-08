/*
   Main game loop
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Wrestler.h"
#include "LocationalMap.h"
#include "Logic.h"
#include "PlayerView.h"
#include "MainMenu.h"
#include "Terrain.h"
#include "Profile.h"
#include "Projectile.h"

int main(int argc, char** argv)
{
    LocationalMap loc_map;
    loc_map.init(800, 600, 30);

    // create main window
    sf::RenderWindow App(sf::VideoMode(800,600,32), "Sumo Slammers - SFML");

    // vectors of collidable objects and set of collisions
    std::vector<Collidable*> actors;
    std::vector<std::set<long int> > collision_sets;

    // Create menu
    MainMenu menu(800, 600);

    // Create profile
    Profile profile;
    profile.setLives(3);
    profile.setCharacter("Fumio");
    profile.setLevel("Generic Level");

    // create wrestlers
    Wrestler human_sumo;
    human_sumo.init(30, 30, 200, 290);
    human_sumo.setIsHuman(true);
    human_sumo.setIsWrestler(true);
    human_sumo.setHasProjectile(false);

    Wrestler ai_sumo;
    ai_sumo.init(30, 30, 400, 300);
    ai_sumo.setIsHuman(false);
    ai_sumo.setIsWrestler(true);
    ai_sumo.setHasProjectile(false);

    Wrestler ai_sumo2;
    ai_sumo2.init(30, 30, 400, 330);
    ai_sumo2.setIsHuman(false);
    ai_sumo2.setIsWrestler(true);
    ai_sumo2.setHasProjectile(false);

    Wrestler ai_sumo3;
    ai_sumo3.init(30, 30, 400, 360);
    ai_sumo3.setIsHuman(false);
    ai_sumo3.setIsWrestler(true);
    ai_sumo3.setHasProjectile(false);

    // create a projectile
    Projectile proj;
    proj.init(30, 30, 370, 300);
    proj.setIsWrestler(false);
    proj.setHasProjectile(true);

    actors.push_back(&human_sumo);
    actors.push_back(&ai_sumo);
    actors.push_back(&ai_sumo2);
    actors.push_back(&ai_sumo3);
    actors.push_back(&proj);
    
    // create view object of collidables
    PlayerView view;
    view.init();

    // create game timer used to keep things synched
    sf::Clock timer;
    const int level[] =
        {
            66, 67, 67, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 67, 67, 68,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            78, 79, 80, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 78, 79, 80,
            90, 91, 92, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 90, 91, 92,
            102, 103, 104, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 102, 103, 104,
            114, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 116,
        };

    // create the tilemap from the level definition
    Terrain map;
    if (!map.load("resources/roundwalls.png", sf::Vector2u(32, 32), level, 25, 20))
        return -1;

    // start main loop
    while(App.isOpen())
    {
        // process events
        sf::Event Event;
        while(App.pollEvent(Event))
        {
            // Exit
            if(Event.type == sf::Event::Closed)
                App.close();
        }

        // Menu status indicating game should be playing
        if (menu.getStatus() == 1)
        {
            //Don't update the game logic unless a certain amount of time has passed
            if(timer.getElapsedTime().asSeconds() > 1.0/60)
            {
                timer.restart();

                // set speeds of wrestlers
                for (int i=0; i<actors.size(); i++) {
                    if (actors[i]->isWrestler()) {
                        if (dynamic_cast<Wrestler*>(actors[i])->isHuman())
                            getInputSetSpd(actors[i], loc_map, actors, "");
                        else
                            setAISpd(actors[i], loc_map, actors);
                    }
                }

                // add wrestlers to locational map
                loc_map.addFuture(actors);

                // check for collisions, need to check if results of collisions cause new collisions and compute again
                collision_sets = calcCollision(loc_map, actors);
                while (collision_sets.size() > 0){
                    loc_map.clearCells();
                    loc_map.addFuture(actors);

                    collision_sets = calcCollision(loc_map, actors);
                }

                moveActors(actors);

                // clear location map
                loc_map.clearCells();
                collision_sets.clear();
            }

            // clear screen and fill with blue
            App.clear(sf::Color::Blue);

            // TODO have basic shape (rectangle?) for WrestlerView objects
            // associated with created actors and draw them
            view.drawActors(App, actors);
            view.drawHUD(App, profile);
            view.drawStaminaBar(App, actors[0]);
        }

        // menu status indicating that menu should be up
        else
        {
            menu.navigate(App);
            menu.draw(App);
        }

        // display
        App.display();
    }

    // Done.
    return 0;
}
