#ifndef AIVIEW_H
#define AIVIEW_H
#include "SFML/Audio.hpp"
#include "Collidable.h"
#include "LocationalMap.h"

class AIView
{
    public:
        AIView();
        virtual ~AIView();

        void setAISpd(Collidable* ai_sumo, LocationalMap& loc_map,
        std::vector<Collidable*>& actors, sf::Sound *sound);
    protected:
    private:
};

#endif // AIVIEW_H
