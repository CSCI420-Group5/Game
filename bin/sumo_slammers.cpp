/*
   Main game loop
 */

#include <SFML/Graphics.hpp>
#include "Wrestler.h"
#include "LocationalMap.h"
#include "Logic.h"
#include "FumioView.h"
#include "MainMenu.h"

#include <iostream>

int main(int argc, char** argv)
{
    LocationalMap loc_map;
    loc_map.init(800, 600, 20);

    // create main window
    sf::RenderWindow App(sf::VideoMode(800,600,32), "Sumo Slammers - SFML");

    // TODO when we have more wrestlers, create a vector and loop through them?
    std::vector<Wrestler> wrestlers;

    // Create menu
    MainMenu menu(800, 600);

    // create wrestlers
    Wrestler human_sumo;
    human_sumo.init(20, 20, 200, 290);
    human_sumo.setIsHuman(true);

    Wrestler ai_sumo;
    ai_sumo.init(20, 20, 400, 300);
    ai_sumo.setIsHuman(false);

    wrestlers.push_back(human_sumo);
    wrestlers.push_back(ai_sumo);
    FumioView view;

    // create game timer used to keep things synched
    sf::Clock timer;

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

                // add wrestlers to locational map
                loc_map.add(wrestlers[0]);
                loc_map.add(wrestlers[1]);

                // check for collisions
                for (int i=0; i<loc_map.getRows(); i++) {
                    for (int j=0; j<loc_map.getCols(); j++) {
                        std::vector<int> tmp = loc_map.getCell(i, j);
                        // if there's a collision
                        if (tmp.size() >= 2) {
                            calcCollision(tmp, wrestlers);
                            loc_map.clearCells();
                            App.clear(sf::Color::Blue);
                            view.drawWrestlers(&App, wrestlers);
                            App.display();
                            continue;
                        }
                    }
                }

                // move human controlled wrestler
                getInputAndMove(wrestlers[0]);

                // move ai controlled wrestler
                moveAI(wrestlers[1], wrestlers[0]);

                // clear location map
                loc_map.clearCells();
            }

            // clear screen and fill with blue
            App.clear(sf::Color::Blue);

            // TODO have basic shape (rectangle?) for WrestlerView objects
            // associated with created wrestlers and draw them
            view.drawWrestlers(&App, wrestlers);
        }


        // menu status indicating that menu should be up
        if (menu.getStatus() == 0)
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
