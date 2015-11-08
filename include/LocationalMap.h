#ifndef LOCATIONALMAP_H
#define LOCATIONALMAP_H
#include "Wrestler.h"


class LocationalMap
{
    public:
        LocationalMap();
        // virtual ~LocationalMap(); commented out due to crashing
        void init(int scn_width, int scn_height, int cell_sz, const int *a);

        void addFuture(std::vector<Collidable*>& actors);
        void addCurrent(std::vector<Collidable*>& actors);

        std::vector<long int> getCell(int i, int j);
        void clearCells();
        void printCells();
        const int* accessible; //0 and 1 indicates whether a tile is accessable
        int getCols();
        int getRows();
    protected:
    private:
        int cell_size;
        int screen_w;
        int screen_h;
        int cols;
        int rows;

        std::vector<long int> *cells; //Will be a 2D array in row-major order
};

#endif // LOCATIONALMAP_H
