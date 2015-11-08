#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include "SFML/Graphics.hpp"
#include "Collidable.h"
#include "Profile.h"


class PlayerView
{
    public:
        PlayerView();
        virtual ~PlayerView();

        void init();
        void drawActors(sf::RenderWindow& App, std::vector<Collidable*> actors);
        void drawHUD(sf::RenderWindow& App, Profile profile);
    protected:
    private:
        void setSprite(Collidable* actor);
        sf::Texture sprite_sheet;
        sf::Sprite sprite;
        sf::Font font;
};

#endif // PLAYERVIEW_H
