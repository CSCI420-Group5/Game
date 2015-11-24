#include "LocationalMap.h"
#include "Wrestler.h"
#include "iostream"

LocationalMap::LocationalMap()
{
    //ctor
}

void LocationalMap::init(int lev_width, int lev_height, int cell_sz,
std::vector<int>& tiles)
{
    //cell_size should be divisible by screen width and height to work correctly
    cell_size = cell_sz;
    level_w = lev_width;
    level_h = lev_height;
    cols = lev_width / cell_size;
    rows = lev_height / cell_size;

    //In case cell size is not evenly divisible by the screen
    /*if (cols < lev_width*cell_size){
        cols++;
    }
    if (rows < lev_height*cell_size){
        rows++;
    }*/

    cells = new Cell[rows*cols];

    for (unsigned int i = 0; i < tiles.size(); i++){
        if (tiles[i] == 207 || tiles[i] == 116){
            cells[i].setStandable(false);
        }
        else{
            cells[i].setStandable(true);
        }
    }
}

void LocationalMap::printCells()
//For debugging purposes
{
    int i;
    int j;

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            std::cout << cells[i*cols+j].getIDs().size() << " ";
        }
        std::cout << std::endl;
    }
}

Cell LocationalMap::getCell(int i, int j)
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
        while((height + cell_size) <= actors[w]->getMovedPos().y && height <= level_h){
            height += cell_size;
            i++;
        }
        while(height < (actors[w]->getMovedPos().y + actors[w]->getHeight()) && height <= level_h){
            add_rows.push_back(i);
            height += cell_size;
            i++;
        }

        //Find all of the j columns that the object occupies
        //And add the object to the cell list for each row for each column
        while((width + cell_size) <= actors[w]->getMovedPos().x && width <= level_w){
            width += cell_size;
            j++;
        }
        while(width < (actors[w]->getMovedPos().x + actors[w]->getWidth()) && width <= level_w){
            for (n = 0; n < add_rows.size(); n++){
                cells[add_rows[n]*cols+j].addID(actors[w]->getID());
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
        while((height + cell_size) <= actors[w]->getPos().y && height <= level_h){
            height += cell_size;
            i++;
        }
        while(height < (actors[w]->getPos().y + actors[w]->getHeight()) && height <= level_h){
            add_rows.push_back(i);
            height += cell_size;
            i++;
        }

        //Find all of the j columns that the object occupies
        //And add the object to the cell list for each row for each column
        while((width + cell_size) <= actors[w]->getPos().x && width <= level_w){
            width += cell_size;
            j++;
        }
        while(width < (actors[w]->getPos().x + actors[w]->getWidth()) && width <= level_w){
            for (n = 0; n < add_rows.size(); n++){
                cells[add_rows[n]*cols+j].addID(actors[w]->getID());
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
            cells[i*cols+j].clearIDs();
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
int LocationalMap::getLevelWidth()
{
    return level_w;
}
int LocationalMap::getLevelHeight()
{
    return level_h;
}

//
//LocationalMap::~LocationalMap()
//{
//    delete cells;
//}
