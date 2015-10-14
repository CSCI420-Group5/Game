#include "FumioView.h"
#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "iostream"

FumioView::FumioView()
{
    //ctor
}

void FumioView::init()
{
    //Set sprite sheet
}

void FumioView::drawWrestlers(sf::RenderWindow *App, std::vector<Wrestler> wrestlers)
{
    //Sort the list of wrestlers based on their y position (depth)
    std::sort(wrestlers.begin(), wrestlers.end());

    //Draw wrestlers with boxes holding positions for now, green for player and red for ai
    for(unsigned int i = 0; i < wrestlers.size(); i++){
        sf::RectangleShape wrest_box(sf::Vector2f(wrestlers[i].getWidth(), wrestlers[i].getHeight()));
        wrest_box.setPosition(wrestlers[i].getX(), wrestlers[i].getY());

        if(wrestlers[i].isHuman()){
            wrest_box.setFillColor(sf::Color::Green);
        }
        else{
            wrest_box.setFillColor(sf::Color::Red);
        }

        App->draw(wrest_box);
    }
}

FumioView::~FumioView()
{
    //dtor
}
