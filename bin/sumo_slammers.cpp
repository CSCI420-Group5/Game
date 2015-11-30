/*
   Main game loop
 */

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Wrestler.h"
#include "LocationalMap.h"
#include "Logic.h"
#include "PlayerView.h"
#include "MainMenu.h"
#include "LevelMenu.h"
#include "Terrain.h"
#include "Profile.h"
#include "Projectile.h"
#include "LevelHandler.h"

int main(int argc, char** argv)
{

    // create main window
    sf::RenderWindow App(sf::VideoMode(800,608,32), "Sumo Slammers - SFML");

    // vectors of collidable objects and set of collisions
    std::vector<Collidable*> actors;
    std::vector<std::set<long int> > collision_sets;

    // start main loop
    while(App.isOpen())
    {
        LocationalMap loc_map;
        sf::View sf_view(sf::Vector2f(400, 304), sf::Vector2f(800, 608));
        App.setView(sf_view);
        // Create menu
        MainMenu main_menu;
        main_menu.init(App.getSize().x, App.getSize().y);
        LevelMenu level_menu;
        level_menu.init(App.getSize().x, App.getSize().y);
        int cur_menu = 0;
        bool main_menu_active = true;
        std::string level_name = "";

        // Create profile
        Profile profile;

        // create view object of collidables
        PlayerView view;
        view.init();

        // create game timer used to keep things synched
        sf::Clock timer;

        //Will create the tilemap from the level definition
        LevelHandler lev_handler;
        Terrain level;
        Terrain layer;

        //Will be initialized after level select
        Wrestler human_sumo;
        int num_bad_guys = 0;
        bool game_over = false;
        bool game_won;
        bool exit_app = false;

        while (!game_over) {
            // process events
            sf::Event Event;
            while(App.pollEvent(Event))
            {
                // Exit
                if(Event.type == sf::Event::Closed) {
                    App.close();
                    game_over = true;
                    exit_app = true;
                }

                //Menu input
                else if(Event.type == sf::Event::KeyPressed){
                    switch(cur_menu){
                        case 0: main_menu_active = main_menu.navigate(App,
                                        Event, exit_app); break;
                        case 1: level_name = level_menu.navigate(Event); break;
                    }
                }
            }

            // menu status indicating that main menu should be up
            if (cur_menu == 0)
            {
                if(!main_menu_active){
                    cur_menu = 1;
                }
                else if (exit_app) {
                    game_over = true;
                }
                else {
                    main_menu.draw(App);
                }
            }

            // menu status indicating that level select should be up
            else if (cur_menu == 1)
            {
                if(level_name != ""){
                    //Load the level
                    profile.setLives(3);
                    lev_handler.loadLevel(level, layer, loc_map, level_name,
                            profile, num_bad_guys);

                    //Initialize human wrestler
                    human_sumo.init(30, 30, lev_handler.getCheckpoint(profile).x, lev_handler.getCheckpoint(profile).y);
                    human_sumo.setIsHuman(true);
                    human_sumo.setIsWrestler(true);
                    human_sumo.setHasProjectile(false);
                    human_sumo.setCharacter("Fumio");
                    profile.setCharacter(human_sumo.getName());
                    actors.push_back(&human_sumo);

                    cur_menu = 2;
                }
                else{
                    level_menu.draw(App);
                }
            }

            // Menu status indicating game should be playing
            else if (cur_menu == 2)
            {
                if (profile.livesRemaining() > 0 && num_bad_guys > 0) {
                    //Don't update the game logic unless a certain amount of time has passed
                    if(timer.getElapsedTime().asSeconds() > 1.0/60)
                    {
                        timer.restart();

                        // set speeds of wrestlers
                        for (unsigned int i=0; i<actors.size(); i++) {
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
                        int fail_safe = 0;
                        while (collision_sets.size() > 0 && fail_safe < 100){
                            loc_map.clearCells();
                            loc_map.addFuture(actors);

                            collision_sets = calcCollision(loc_map, actors);
                            fail_safe++;
                        }

                        moveActors(actors, loc_map, profile, lev_handler, sf_view,
                                num_bad_guys);

                        // clear location map
                        loc_map.clearCells();
                        collision_sets.clear();
                    }

                    //recenter view if this will not move it outside of the map
                    if ((actors[0]->getPos().x - sf_view.getSize().x/2 >= 0) &&
                            (actors[0]->getPos().x + sf_view.getSize().x/2 <= loc_map.getLevelWidth())){

                        sf_view.setCenter(actors[0]->getPos().x, sf_view.getCenter().y);
                    }
                    else if(actors[0]->getPos().x < sf_view.getSize().x/2){
                        sf_view.setCenter(sf_view.getSize().x/2, sf_view.getCenter().y);
                    }
                    else if(actors[0]->getPos().x > loc_map.getLevelWidth() - sf_view.getSize().x/2){
                        sf_view.setCenter(loc_map.getLevelWidth() - sf_view.getSize().x/2, sf_view.getCenter().y);
                    }
                    if ((actors[0]->getPos().y - sf_view.getSize().y/2 >= 0) &&
                            (actors[0]->getPos().y + sf_view.getSize().y/2 <= loc_map.getLevelHeight())){

                        sf_view.setCenter(sf_view.getCenter().x, actors[0]->getPos().y);
                    }
                    else if(actors[0]->getPos().y < sf_view.getSize().y/2){
                        sf_view.setCenter(sf_view.getCenter().x, sf_view.getSize().y/2);
                    }
                    else if(actors[0]->getPos().y > loc_map.getLevelHeight() - sf_view.getSize().y/2){
                        sf_view.setCenter(sf_view.getCenter().x, loc_map.getLevelHeight() - sf_view.getSize().y/2);
                    }
                    App.setView(sf_view);

                    //Add actors to vector if they are just off screen in the positive x direction
                    lev_handler.spawnActors(actors, sf_view.getCenter().x + sf_view.getSize().x/2);

                    //Record that player at the next checkpoint when close enough
                    lev_handler.checkCheckpoints(actors[0], profile);

                    // clear screen
                    App.clear(sf::Color::Green);

                    //Draw things
                    view.drawLevel(App, level, layer);
                    view.drawActors(App, actors);
                    view.drawStaminaBar(App, actors[0]);
                    view.drawHUD(App, profile);
                }
                else {
                    game_over = true;
                    if (profile.livesRemaining() > 0)
                        game_won = true;
                    else
                        game_won = false;
                }
            }

            // display
            App.display();
        }

        // got here if game ended
        if (exit_app == false) { 
            if (game_won == true) {
                main_menu.drawWon(App);
            }
            else {
                main_menu.drawLose(App);
            }
            while (timer.getElapsedTime().asSeconds() < 4)
                App.display();

            game_over = false;
            cur_menu = 0;
            actors.clear();
            collision_sets.clear();
            num_bad_guys = 0;
            main_menu_active = true;
            level_name = "";
        }
    }

    // Done.
    return 0;
}
