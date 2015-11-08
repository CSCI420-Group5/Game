#include "PlayerView.h"
#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "iostream"
#include "tinyxml2.h"
#include <sstream>

void PlayerView::setSprite(Collidable* actor)
{
    if(actor->isHuman()) {
        Wrestler *w = dynamic_cast<Wrestler*>(actor);
        int state = w->getCurrentState();
        // standings still, facing right
        if (state == 0) {
            sprite.setTextureRect(sf::IntRect(100,0,100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // standings still, facing left 
        if (state == 1) {
            sprite.setTextureRect(sf::IntRect(100,0,-100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // running right 1 
        if (state == 2) {
            sprite.setTextureRect(sf::IntRect(0,0,100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // running right 2 
        if (state == 3) {
            sprite.setTextureRect(sf::IntRect(200,0,100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // running left 1 
        if (state == 4) {
            sprite.setTextureRect(sf::IntRect(100,0,-100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // running left 2
        if (state == 5) {
            sprite.setTextureRect(sf::IntRect(300,0,-100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // running up 1
        if (state == 7) {
            sprite.setTextureRect(sf::IntRect(400,0,100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // running up 2
        if (state == 8) {
            sprite.setTextureRect(sf::IntRect(600,0,100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // running down 1
        if (state == 10) {
            sprite.setTextureRect(sf::IntRect(900,0,-100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // running down 2
        if (state == 11) {
            sprite.setTextureRect(sf::IntRect(1100,0,-100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // dash right
        if (state == 12) {
            sprite.setTextureRect(sf::IntRect(1200,0,100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // dash left
        if (state == 13) {
            sprite.setTextureRect(sf::IntRect(1300,0,-100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // dash down
        if (state == 14) {
            sprite.setTextureRect(sf::IntRect(1400,0,100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
        // dash up
        if (state == 15) {
            sprite.setTextureRect(sf::IntRect(1300,0,100,100));
            sf::Vector2f human_pos = actor->getPos();
            sprite.setPosition(human_pos.x-(100-actor->getWidth())/2,human_pos.y
            -(80-actor->getHeight()));
        }
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

    //Draw wrestlers with boxes holding positions for now, green for player and red for ai
    for(unsigned int i = 0; i < actors.size(); i++){
        sf::RectangleShape wrest_box(sf::Vector2f(actors[i]->getWidth(),
        actors[i]->getHeight()));
        wrest_box.setPosition(actors[i]->getPos());

        if(actors[i]->isHuman()){
            setSprite(actors[i]);
            //sprite.setTextureRect(sf::IntRect(0,0,100,100));
            //sf::Vector2f human_pos = actors[i]->getPos();
            //sprite.setPosition(human_pos.x - (100-actors[i]->getWidth())/2, human_pos.y - (80-actors[i]->getHeight()));
            App.draw(sprite);
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

PlayerView::~PlayerView()
{
    //dtor
}
