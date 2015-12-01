#ifndef AIVIEW_H
#define AIVIEW_H
#include "Collidable.h"
#include "LocationalMap.h"


class AIView
{
    public:
        AIView();
        virtual ~AIView();

        void setAISpd(Collidable* ai_sumo, LocationalMap& loc_map, std::vector<Collidable*>& actors);
    protected:
    private:
};

#endif // AIVIEW_H
