#ifndef FUMIOVIEW_H
#define FUMIOVIEW_H
#include "SFML/Graphics.hpp"
#include "Wrestler.h"


class FumioView
{
    public:
        FumioView();
        virtual ~FumioView();

        void init();
        void drawWrestlers(sf::RenderWindow *App, std::vector<Wrestler> wrestlers);
    protected:
    private:
        sf::Texture sprite_sheet;
};

#endif // FUMIOVIEW_H
