#include "PlayerView.h"
#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "iostream"
#include <sstream>

PlayerView::PlayerView()
{
    //ctor
}

void PlayerView::init()
{
    font.loadFromFile("arial.ttf");
}

void PlayerView::drawActors(sf::RenderWindow& App, std::vector<Collidable*> actors)
{
    //Sort the list of wrestlers based on their y position (depth)
    std::sort(actors.begin(), actors.end());

    //Draw wrestlers with boxes holding positions for now, green for player and red for ai
    for(unsigned int i = 0; i < actors.size(); i++){
        sf::RectangleShape wrest_box(sf::Vector2f(actors[i]->getWidth(),
        actors[i]->getHeight()));
        wrest_box.setPosition(actors[i]->getPos());

        if(actors[i]->isHuman()){
            wrest_box.setFillColor(sf::Color::Green);
        }
        else{
            wrest_box.setFillColor(sf::Color::Red);
        }

        App.draw(wrest_box);
    }
}

void PlayerView::drawHUD(sf::RenderWindow& App, Profile profile)
{
    sf::Text lives_txt;
    std::stringstream lives;
    lives << profile.livesRemaining();
    lives_txt.setString(profile.getCharacter() + ": Lives x" + lives.str());
    lives_txt.setFont(font);
    lives_txt.setColor(sf::Color::White);
    lives_txt.setPosition(sf::Vector2f(0, 590 - lives_txt.getGlobalBounds().height));

    sf::Text level_txt;
    level_txt.setString(profile.getLevel());
    level_txt.setFont(font);
    level_txt.setColor(sf::Color::White);
    level_txt.setPosition(sf::Vector2f(790 - level_txt.getGlobalBounds().width, 0));

    App.draw(lives_txt);
    App.draw(level_txt);
}

PlayerView::~PlayerView()
{
    //dtor
}
