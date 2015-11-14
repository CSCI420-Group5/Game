#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H
#include "Terrain.h"
#include "LocationalMap.h"


class LevelHandler
{
    public:
        LevelHandler();
        virtual ~LevelHandler();

        void loadLevel1(Terrain& level, Terrain& layer, LocationalMap& loc_map);
        void loadLevel2(Terrain& level, Terrain& layer, LocationalMap& loc_map);
    protected:
    private:
};

#endif // LEVELHANDLER_H
