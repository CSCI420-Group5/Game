#include "PlayerView.h"
#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "iostream"
#include "tinyxml2.h"
#include <sstream>
#include <string>

void PlayerView::setSprite(Collidable* actor)
{
    Wrestler *w = dynamic_cast<Wrestler*>(actor);
    Wrestler::SpriteState state = w->getCurSpriteState();
    sf::Vector2f pos = w->getPos();
    sprite.setPosition(pos.x-(100-w->getWidth())/2,pos.y-(80-w->getHeight()));

    // standings still, facing right
    if (state == Wrestler::STAND_RIGHT) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(100,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(100,100,100,100));
    }
    // standings still, facing left 
    if (state == Wrestler::STAND_LEFT) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(200,0,-100,100));
        else
            sprite.setTextureRect(sf::IntRect(200,100,-100,100));
    }
    // running right 1 
    if (state == Wrestler::RUN_RIGHT1) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(0,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(0,100,100,100));
    }
    // running right 2 
    if (state == Wrestler::RUN_RIGHT2) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(200,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(200,100,100,100));
    }
    // running left 1 
    if (state == Wrestler::RUN_LEFT1) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(100,0,-100,100));
        else
            sprite.setTextureRect(sf::IntRect(100,100,-100,100));
    }
    // running left 2
    if (state == Wrestler::RUN_LEFT2) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(300,0,-100,100));
        else
            sprite.setTextureRect(sf::IntRect(300,100,-100,100));
    }
    // standing up
    if (state == Wrestler::STAND_UP) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(500,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(500,100,100,100));
    }
    // running up 1
    if (state == Wrestler::RUN_UP1) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(400,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(400,100,100,100));
    }
    // running up 2
    if (state == Wrestler::RUN_UP2) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(600,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(600,100,100,100));
    }
    // standing down
    if (state == Wrestler::STAND_DOWN) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(1100,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(1100,100,100,100));
    }
    // running down 1
    if (state == Wrestler::RUN_DOWN1) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(800,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(800,100,100,100));
    }
    // running down 2
    if (state == Wrestler::RUN_DOWN2) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(1000,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(1000,100,100,100));
    }
    // dash right
    if (state == Wrestler::DASH_RIGHT) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(1200,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(1200,100,100,100));
    }
    // dash left
    if (state == Wrestler::DASH_LEFT) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(1300,0,-100,100));
        else
            sprite.setTextureRect(sf::IntRect(1300,100,-100,100));
    }
    // dash down
    if (state == Wrestler::DASH_DOWN) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(1400,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(1400,100,100,100));
    }
    // dash up
    if (state == Wrestler::DASH_UP) {
        if (w->isHuman())
            sprite.setTextureRect(sf::IntRect(1300,0,100,100));
        else
            sprite.setTextureRect(sf::IntRect(1300,100,100,100));
    }
}

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

    //Draw wrestlers
    for(unsigned int i = 0; i < actors.size(); i++){
        setSprite(actors[i]);
        App.draw(sprite);
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

void PlayerView::drawStaminaBar(sf::RenderWindow& App, Collidable* player)
{
    Wrestler* w = dynamic_cast<Wrestler*>(player);

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
