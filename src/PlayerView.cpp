#include "PlayerView.h"
#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "iostream"

PlayerView::PlayerView()
{
    //ctor
}

void PlayerView::init()
{
    //Set sprite sheet
}

void PlayerView::drawActors(sf::RenderWindow *App, std::vector<Collidable> actors)
{
    //Sort the list of wrestlers based on their y position (depth)
    std::sort(actors.begin(), actors.end());

    //Draw wrestlers with boxes holding positions for now, green for player and red for ai
    for(unsigned int i = 0; i < actors.size(); i++){
        sf::RectangleShape wrest_box(sf::Vector2f(actors[i].getWidth(), actors[i].getHeight()));
        wrest_box.setPosition(actors[i].getPos());

        if(actors[i].isHuman()){
            wrest_box.setFillColor(sf::Color::Green);
        }
        else{
            wrest_box.setFillColor(sf::Color::Red);
        }

        App->draw(wrest_box);
    }
}

PlayerView::~PlayerView()
{
    //dtor
}
