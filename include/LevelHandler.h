#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H
#include "Terrain.h"
#include "LocationalMap.h"
#include "string"
#include "Collidable.h"
#include "Profile.h"


class LevelHandler
{
    public:
        LevelHandler();
        virtual ~LevelHandler();

        void loadLevel(Terrain& level, Terrain& layer, LocationalMap& loc_map,
                       std::string file_name, Profile& profile);
        void spawnActors(std::vector<Collidable*> &actors, int scrn_right_side);
        void checkCheckpoints(Collidable* player, Profile& profile);
        sf::Vector2f getCheckpoint(Profile& profile);
//        void loadLevel2(Terrain& level, Terrain& layer, LocationalMap& loc_map);
    protected:
    private:
        std::vector<Collidable*> future_actors;
        std::vector<sf::Vector2f> checkpoints;
};

#endif // LEVELHANDLER_H
