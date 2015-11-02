#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include "SFML/Graphics.hpp"
#include "Wrestler.h"


class PlayerView
{
    public:
        PlayerView();
        virtual ~PlayerView();

        void init();
        void drawActors(sf::RenderWindow *App, std::vector<Collidable> actors);
    protected:
    private:
        sf::Texture sprite_sheet;
};

#endif // PLAYERVIEW_H
