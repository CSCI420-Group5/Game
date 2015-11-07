#include "PlayerView.h"
#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "iostream"
#include "tinyxml2.h"
#include <sstream>
#include <string>

PlayerView::PlayerView()
{
    //ctor
}

void PlayerView::init()
{
    font.loadFromFile("resources/arial.ttf");

    tinyxml2::XMLDocument doc;
    bool loadFail = doc.LoadFile("resources/resources.xml");
    if (!loadFail) {
        tinyxml2::XMLElement* file_element =
        doc.FirstChildElement("resources")
        ->FirstChildElement("wrestlerSpriteSheet");

        std::string file_name = file_element->GetText();
        sprite_sheet.loadFromFile(file_name);
        sprite.setTexture(sprite_sheet);
    }

}

bool sortByDepth (const Collidable* actor1, const Collidable* actor2)
{
    return (actor1->getPos().y < actor2->getPos().y);
}

void PlayerView::drawActors(sf::RenderWindow& App, std::vector<Collidable*> actors)
{
    //Sort the list of wrestlers based on their y position (depth)
    std::sort(actors.begin(), actors.end(), sortByDepth);

    //Draw wrestlers with boxes holding positions for now, green for player and red for ai
    for(unsigned int i = 0; i < actors.size(); i++){
        sf::RectangleShape wrest_box(sf::Vector2f(actors[i]->getWidth(),
        actors[i]->getHeight()));
        wrest_box.setPosition(actors[i]->getPos());

        if(actors[i]->isHuman()){
            sprite.setTextureRect(sf::IntRect(0,0,100,100));
            sf::Vector2f human_pos = actors[i]->getPos();
            sprite.setPosition(human_pos.x - (100-actors[i]->getWidth())/2, human_pos.y - (80-actors[i]->getHeight()));
            wrest_box.setFillColor(sf::Color::Green);
            App.draw(wrest_box);
            App.draw(sprite);
//            wrest_box.setTexture(&sprite_sheet);
        }
        else{
            wrest_box.setFillColor(sf::Color::Red);
            App.draw(wrest_box);
        }
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

void PlayerView::drawStaminaBar(sf::RenderWindow& App, Wrestler* w)
{
    std::string stamStr;
    std::stringstream convert;
    convert << w->getStamina();
    stamStr = convert.str();

    sf::Text stam_txt;
    stam_txt.setString(stamStr);
    stam_txt.setFont(font);
    stam_txt.setColor(sf::Color::White);
    stam_txt.setPosition(sf::Vector2f(100, 100));

    App.draw(stam_txt);
}

PlayerView::~PlayerView()
{
    //dtor
}
