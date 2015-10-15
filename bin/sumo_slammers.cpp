/*
   Main game loop
   Github example
 */

#include <SFML/Graphics.hpp>
#include "Wrestler.h"
#include "LocationalMap.h"
#include "Logic.h"
#include "FumioView.h"

int main(int argc, char** argv)
{
    LocationalMap loc_map;
    loc_map.init(800, 600, 25);

    // create main window
    sf::RenderWindow App(sf::VideoMode(800,600,32), "Sumo Slammers - SFML");

    // TODO when we have more wrestlers, create a vector and loop through them?
    std::vector<Wrestler> wrestlers;

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
        sf::Time time = timer.restart();

        // move human controlled wrestler
        getInputAndMove(wrestlers[0], time);

        // move ai controlled wrestler
        moveAI(wrestlers[1], wrestlers[0], time);

        // clear screen and fill with blue
        App.clear(sf::Color::Blue);

        // TODO have basic shape (rectangle?) for WrestlerView objects
        // associated with created wrestlers and draw them
        view.drawWrestlers(&App, wrestlers);


        // display
        App.display();
    }

    // Done.
    return 0;
}
