#ifndef LOCATIONALMAP_H
#define LOCATIONALMAP_H
#include "Wrestler.h"


class LocationalMap
{
    public:
        LocationalMap();
        virtual ~LocationalMap();

        void init(int scn_width, int scn_height, int cell_sz);
        void add(Wrestler sumo);
        std::vector<int> getCell(int i, int j);
        void clearCells();
        void printCells();

        int getCols();
        int getRows();
    protected:
    private:
        int cell_size;
        int screen_w;
        int screen_h;
        int cols;
        int rows;
        std::vector<int> *cells; //Will be a 2D array in row-major order
};

#endif // LOCATIONALMAP_H
