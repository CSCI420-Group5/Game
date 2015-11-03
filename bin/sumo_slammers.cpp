/*
   Main game loop
 */

#include <SFML/Graphics.hpp>
#include "Wrestler.h"
#include "LocationalMap.h"
#include "Logic.h"
#include "PlayerView.h"
#include "MainMenu.h"
#include "Terrain.h"
#include "Profile.h"

int main(int argc, char** argv)
{
    LocationalMap loc_map;
    loc_map.init(800, 600, 20);

    // create main window
    sf::RenderWindow App(sf::VideoMode(800,600,32), "Sumo Slammers - SFML");

    // TODO when we have more wrestlers, create a vector and loop through them?
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
    human_sumo.init(20, 20, 200, 290);
    human_sumo.setIsHuman(true);

    Wrestler ai_sumo;
    ai_sumo.init(20, 20, 400, 300);
    ai_sumo.setIsHuman(false);

    Wrestler ai_sumo2;
    ai_sumo2.init(20, 20, 400, 330);
    ai_sumo2.setIsHuman(false);

    Wrestler ai_sumo3;
    ai_sumo3.init(20, 20, 400, 360);
    ai_sumo3.setIsHuman(false);

    actors.push_back(&human_sumo);
    actors.push_back(&ai_sumo);
    actors.push_back(&ai_sumo2);
    actors.push_back(&ai_sumo3);
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

                // set speed for human controlled wrestler
                Wrestler *w = dynamic_cast<Wrestler*>(actors[0]);
                getInputSetSpd(w);

                // set speed for ai controlled wrestler
                setAISpd(actors[1], actors[0]);
                setAISpd(actors[2], actors[0]);
                setAISpd(actors[3], actors[0]);


                // add wrestlers to locational map
                loc_map.add(actors);

                // check for collisions, need to check if results of collisions cause new collisions and compute again
                collision_sets = calcCollision(loc_map, actors);
                while (collision_sets.size() > 0){
                    loc_map.clearCells();
                    loc_map.add(actors);

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
