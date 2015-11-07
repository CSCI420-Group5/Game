#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include "SFML/Graphics.hpp"
#include "Collidable.h"
#include "Profile.h"
#include "Wrestler.h"


class PlayerView
{
    public:
        PlayerView();
        virtual ~PlayerView();

        void init();
        void drawActors(sf::RenderWindow& App, std::vector<Collidable*> actors);
        void drawHUD(sf::RenderWindow& App, Profile profile);
        void drawStaminaBar(sf::RenderWindow& App, Collidable* player);

    protected:
    private:
        sf::Texture sprite_sheet;
        sf::Sprite sprite;
        sf::Font font;
};

#endif // PLAYERVIEW_H
