#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H
#include "Terrain.h"
#include "LocationalMap.h"
#include "string"


class LevelHandler
{
    public:
        LevelHandler();
        virtual ~LevelHandler();

        void loadLevel(Terrain& level, Terrain& layer, LocationalMap& loc_map, std::string file_name);
        void loadLevel2(Terrain& level, Terrain& layer, LocationalMap& loc_map);
    protected:
    private:
};

#endif // LEVELHANDLER_H
