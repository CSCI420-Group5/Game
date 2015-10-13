/*
   Main game loop
 */

#include <SFML/Graphics.hpp>
#include "Wrestler.h"
#include "LocationalMap.h"
#include "Logic.h"

int main(int argc, char** argv)
{
    LocationalMap loc_map;
    loc_map.init(800, 600, 25);

    // create main window
    sf::RenderWindow App(sf::VideoMode(800,600,32), "Sumo Slamemrs - SFML");

    // TODO when we have more wrestlers, create a vector and loop through them?

    // create wrestlers
    Wrestler human_sumo;
    human_sumo.init(5, 5);
    human_sumo.setIsHuman(true);

    Wrestler ai_sumo;
    ai_sumo.init(5, 5);
    ai_sumo.setIsHuman(false);

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
        sf::Time time = timer.restart();

        // move human controlled wrestler
        getInputAndMove(human_sumo, time);

        // move ai controlled wrestler
        moveAI(ai_sumo, human_sumo, time);

        // clear screen and fill with blue
        App.clear(sf::Color::Blue);

        // TODO have basic shape (rectangle?) for WrestlerView objects 
        // associated with created wrestlers and draw them

        // display
        App.display();
    }

    // Done.
    return 0;
}
