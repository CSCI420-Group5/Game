#include "LocationalMap.h"
#include "Wrestler.h"
#include "iostream"

LocationalMap::LocationalMap()
{
    //ctor
}

void LocationalMap::init(int scn_width, int scn_height, int cell_sz, const int* a)
{
    //cell_size should be divisible by screen width and height to work correctly
    cell_size = cell_sz;
    screen_w = scn_width;
    screen_h = scn_height;
    cols = scn_width / cell_size;
    rows = scn_height / cell_size;

    //In case cell size is not evenly divisible by the screen
    if (cols < scn_width*cell_size){
        cols++;
    }
    if (rows < scn_height*cell_size){
        rows++;
    }

    cells = new std::vector<long int>[rows*cols];
    std::cout << "cells: " << rows*cols << std::endl;
    std::cout << "rows: " << rows << std::endl;
    std::cout << "cols: " << cols << std::endl;
    //assert (sizeof(a) == sizeof(cells));
    //this->accessible = malloc(sizeof(int) * sizeof(a));
    this->accessible = a;

    int i;
    for(i = 0; i < 30; i++){
        std::cout << accessible[i] << std::endl;
    }
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

void LocationalMap::addFuture(std::vector<Collidable*>& actors)
//adds the int id of a wrestler object to all cells it resides in
{
    for (unsigned int w = 0; w < actors.size(); w++){
        int i = 0; //Index of the cell row
        int height = 0;
        std::vector<int> add_rows;
        int j = 0; //Index of the cell column
        int width = 0;
        size_t n;

        //Find all of the i rows that the object occupies
        while((height + cell_size) <= actors[w]->getMovedPos().y && height <= screen_h){
            height += cell_size;
            i++;
        }
        while(height < (actors[w]->getMovedPos().y + actors[w]->getHeight()) && height <= screen_h){
            add_rows.push_back(i);
            height += cell_size;
            i++;
        }

        //Find all of the j columns that the object occupies
        //And add the object to the cell list for each row for each column
        while((width + cell_size) <= actors[w]->getMovedPos().x && width <= screen_w){
            width += cell_size;
            j++;
        }
        while(width < (actors[w]->getMovedPos().x + actors[w]->getWidth()) && width <= screen_w){
            for (n = 0; n < add_rows.size(); n++){
                cells[add_rows[n]*cols+j].push_back(actors[w]->getID());
            }

            width += cell_size;
            j++;
        }
    }
}

void LocationalMap::addCurrent(std::vector<Collidable*>& actors)
//adds the int id of a wrestler object to all cells it resides in
{
    for (unsigned int w = 0; w < actors.size(); w++){
        int i = 0; //Index of the cell row
        int height = 0;
        std::vector<int> add_rows;
        int j = 0; //Index of the cell column
        int width = 0;
        size_t n;

        //Find all of the i rows that the object occupies
        while((height + cell_size) <= actors[w]->getPos().y && height <= screen_h){
            height += cell_size;
            i++;
        }
        while(height < (actors[w]->getPos().y + actors[w]->getHeight()) && height <= screen_h){
            add_rows.push_back(i);
            height += cell_size;
            i++;
        }

        //Find all of the j columns that the object occupies
        //And add the object to the cell list for each row for each column
        while((width + cell_size) <= actors[w]->getPos().x && width <= screen_w){
            width += cell_size;
            j++;
        }
        while(width < (actors[w]->getPos().x + actors[w]->getWidth()) && width <= screen_w){
            for (n = 0; n < add_rows.size(); n++){
                cells[add_rows[n]*cols+j].push_back(actors[w]->getID());
            }

            width += cell_size;
            j++;
        }
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
