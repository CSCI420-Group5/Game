/*
    Main game loop
    TODO create wrestlers to test Wrestler class
*/

#include <SFML/Graphics.hpp>
#include "Wrestler.h"

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Sumo Slamemrs - SFML");

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

    // TODO get input from human player to move a wrestler around

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

    // TODO have basic shape (rectangle?) for WrestlerView objects associated
    // with created wrestlers and draw them

    // display
    App.display();
  }

  // Done.
  return 0;
}
