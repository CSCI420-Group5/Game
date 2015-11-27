#include "PlayerView.h"
#include "SFML/Graphics.hpp"
#include "Wrestler.h"
#include "Projectile.h"
#include "iostream"
#include "tinyxml2.h"
#include <sstream>
#include <string>

void PlayerView::setSprite(Collidable* actor)
{
    Wrestler *w = dynamic_cast<Wrestler*>(actor);
    Wrestler::SpriteState state = w->getCurSpriteState();
    sf::Vector2f pos = w->getPos();
    sprite.setPosition(pos.x-(100-w->getWidth())/2,pos.y-(90-w->getHeight()));

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
    //Sort the list of Collidables based on their y position (depth)
    std::sort(actors.begin(), actors.end(), sortByDepth);

    //Draw Collidables
    for(unsigned int i = 0; i < actors.size(); i++){
        if (actors[i]->isWrestler()) {
            setSprite(actors[i]);
            App.draw(sprite);
        }
        else {
            Projectile *proj = dynamic_cast<Projectile*>(actors[i]);
            // draw projectile base
            sf::RectangleShape
            proj_box(sf::Vector2f(proj->getWidth(), proj->getHeight()));

            proj_box.setPosition(proj->getPos());
            proj_box.setFillColor(sf::Color::Red);
            App.draw(proj_box);

            // draw projectile ball
            sf::CircleShape ball(8);
            ball.setPosition(proj->getBallPos());
            App.draw(ball);
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
    sf::Vector2f lives_level_coords = App.mapPixelToCoords(sf::Vector2i(0, 590 - lives_txt.getGlobalBounds().height));
    lives_txt.setPosition(lives_level_coords);

    sf::Text level_txt;
    level_txt.setString(profile.getLevel());
    level_txt.setFont(font);
    level_txt.setColor(sf::Color::White);
    sf::Vector2f level_level_coords = App.mapPixelToCoords(sf::Vector2i(790 - level_txt.getGlobalBounds().width, 0));
    level_txt.setPosition(level_level_coords);

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

    //Adjust coords to follow view
    sf::Vector2f stam_level_coords = App.mapPixelToCoords(sf::Vector2i(0, 565));
    sf::Vector2f stam_level_coords2 = App.mapPixelToCoords(sf::Vector2i(230, 575));

    stamBack.setSize(sf::Vector2f(390, 40));
    stamBack.setFillColor(sf::Color(0, 0, 0));
    stamBack.setPosition(stam_level_coords);

    stamBar.setSize(sf::Vector2f((w->getStamina() * 1.5), 20));
    stamBar.setFillColor(sf::Color(250, 50, 50));
    stamBar.setPosition(stam_level_coords2);

    mid.setSize(sf::Vector2f(3,28));
    mid.setFillColor(sf::Color(100, 100, 250));

    App.draw(stamBack);
    App.draw(stamBar);

    mid.setPosition(App.mapPixelToCoords(sf::Vector2i(230, 570)));
    App.draw(mid);
    mid.setPosition(App.mapPixelToCoords(sf::Vector2i(305, 570)));
    App.draw(mid);
    mid.setPosition(App.mapPixelToCoords(sf::Vector2i(380, 570)));
    App.draw(mid);

    //App.draw(stam_txt);
}

PlayerView::~PlayerView()
{
    //dtor
}
