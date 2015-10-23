#include "LocationalMap.h"
#include "Wrestler.h"
#include "iostream"

LocationalMap::LocationalMap()
{
    //ctor
}

void LocationalMap::init(int scn_width, int scn_height, int cell_sz)
{
    //cell_size should be divisible by screen width and height to work correctly
    cell_size = cell_sz;
    screen_w = scn_width;
    screen_h = scn_height;
    cols = scn_width / cell_size;
    rows = scn_height / cell_size;
    cells = new std::vector<long int>[rows*cols];
}

void LocationalMap::printCells()
//For debugging purposes
{
    int i;
    int j;

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            std::cout << cells[i*cols+j].size() << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<long int> LocationalMap::getCell(int i, int j)
//a cell will return a vector of all actor id's in it.
//Can then only compare actors in the same cell to find collisions
{
    return cells[i*cols+j];
}

void LocationalMap::add(Wrestler sumo)
//adds the int id of a wrestler object to all cells it resides in
{
    int i = 0; //Index of the cell row
    int height = 0;
    std::vector<int> add_rows;
    int j = 0; //Index of the cell column
    int width = 0;
    size_t n;

    //Find all of the i rows that the object occupies
    while((height + cell_size) <= sumo.getMovedY() && height < screen_h){
        height += cell_size;
        i++;
    }
    while(height < (sumo.getMovedY() + sumo.getHeight()) && height < screen_h){
        add_rows.push_back(i);
        height += cell_size;
        i++;
    }

    //Find all of the j columns that the object occupies
    //And add the object to the cell list for each row for each column
    while((width + cell_size) <= sumo.getMovedX() && width < screen_w){
        width += cell_size;
        j++;
    }
    while(width < (sumo.getMovedX() + sumo.getWidth()) && width < screen_w){
        for (n = 0; n < add_rows.size(); n++){
            cells[add_rows[n]*cols+j].push_back(sumo.getId());
        }

        width += cell_size;
        j++;
    }
}

void LocationalMap::clearCells()
{
    int i;
    int j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            cells[i*cols+j].clear();
        }
    }
}

int LocationalMap::getCols()
{
    return cols;
}
int LocationalMap::getRows()
{
    return rows;
}

/* LocationalMap::~LocationalMap()
{
    delete cells;
} */
