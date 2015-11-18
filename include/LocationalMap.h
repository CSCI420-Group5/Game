#ifndef LOCATIONALMAP_H
#define LOCATIONALMAP_H
#include "Wrestler.h"
#include "Cell.h"
#include "Terrain.h"


class LocationalMap
{
    public:
        LocationalMap();
//        virtual ~LocationalMap();
        void init(int scn_width, int scn_height, int cell_sz, std::vector<int>& tiles);

        void addFuture(std::vector<Collidable*>& actors);
        void addCurrent(std::vector<Collidable*>& actors);

        Cell getCell(int i, int j);
        void clearCells();
        void printCells();
        int getCols();
        int getRows();
    protected:
    private:
        int cell_size;
        int level_w;
        int level_h;
        int cols;
        int rows;

        Cell *cells; //Will be a 2D array in row-major order
};

#endif // LOCATIONALMAP_H
