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
#include "LevelHandler.h"

int main(int argc, char** argv)
{
    LocationalMap loc_map;

    // create main window
    sf::RenderWindow App(sf::VideoMode(800,608,32), "Sumo Slammers - SFML");
    sf::View sf_view(sf::Vector2f(400, 304), sf::Vector2f(800, 608));
    App.setView(sf_view);

    // vectors of collidable objects and set of collisions
    std::vector<Collidable*> actors;
    std::vector<std::set<long int> > collision_sets;

    // Create menu
    MainMenu menu(800, 608);

    // Create profile
    Profile profile;
    profile.setLives(3);
    profile.setCharacter("Fumio");

    // create wrestlers
    Wrestler human_sumo;
    human_sumo.init(30, 30, 200, 290);
    human_sumo.setIsHuman(true);
    human_sumo.setIsWrestler(true);
    human_sumo.setHasProjectile(false);
    human_sumo.setCharacter(1);

    Wrestler ai_sumo;
    ai_sumo.init(30, 30, 400, 300);
    ai_sumo.setIsHuman(false);
    ai_sumo.setIsWrestler(true);
    ai_sumo.setHasProjectile(false);
    ai_sumo.setCharacter(2);


    Wrestler ai_sumo2;
    ai_sumo2.init(30, 30, 400, 330);
    ai_sumo2.setIsHuman(false);
    ai_sumo2.setIsWrestler(true);
    ai_sumo2.setHasProjectile(false);
    ai_sumo2.setCharacter(2);

    Wrestler ai_sumo3;
    ai_sumo3.init(30, 30, 400, 360);
    ai_sumo3.setIsHuman(false);
    ai_sumo3.setIsWrestler(true);
    ai_sumo3.setHasProjectile(false);
    ai_sumo3.setCharacter(2);

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

    LevelHandler lev_handler;

    // create the tilemap from the level definition
    Terrain level;
    Terrain layer;
    lev_handler.loadLevel(level, layer, loc_map, "resources/levelS.csv");
    profile.setLevel("Level S");

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
                for (unsigned int i=0; i<actors.size(); i++) {
                    if (actors[i]->isWrestler()) {
                        if (dynamic_cast<Wrestler*>(actors[i])->isHuman())
                            getInputSetSpd(actors[i], loc_map, actors, "");
                        //else
                            //setAISpd(actors[i], loc_map, actors);
                    }
                }

                // add wrestlers to locational map
                loc_map.addFuture(actors);

                // check for collisions, need to check if results of collisions cause new collisions and compute again
                collision_sets = calcCollision(loc_map, actors);
                int fail_safe = 0;
                while (collision_sets.size() > 0 && fail_safe < 100){
                    loc_map.clearCells();
                    loc_map.addFuture(actors);

                    collision_sets = calcCollision(loc_map, actors);
                    fail_safe++;
                }

                moveActors(actors, loc_map, profile, sf_view);

                // clear location map
                loc_map.clearCells();
                collision_sets.clear();
            }

            // clear screen and fill with blue
            App.clear(sf::Color::Green);
            App.draw(level);
            App.draw(layer);

            //Draw things
            view.drawActors(App, actors);
            view.drawStaminaBar(App, actors[0]);
            view.drawHUD(App, profile);

            //recenter view if this will not move it outside of the map
            if ((actors[0]->getPos().x - sf_view.getSize().x/2 >= 0) &&
                (actors[0]->getPos().x + sf_view.getSize().x/2 <= loc_map.getLevelWidth())){

                sf_view.setCenter(actors[0]->getPos().x, sf_view.getCenter().y);
            }
            if ((actors[0]->getPos().y - sf_view.getSize().y/2 >= 0) &&
                (actors[0]->getPos().y + sf_view.getSize().y/2 <= loc_map.getLevelHeight())){

                sf_view.setCenter(sf_view.getCenter().x, actors[0]->getPos().y);
            }
            App.setView(sf_view);
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
