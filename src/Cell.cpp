#include "Cell.h"

Cell::Cell()
{
    //ctor
}

void Cell::addID(long int new_id)
{
    ids.push_back(new_id);
}

void Cell::clearIDs()
{
    ids.clear();
}

void Cell::setStandable(bool boolean)
{
    standable = boolean;
}

bool Cell::isStandable()
{
    return standable;
}

std::vector<long int> Cell::getIDs()
{
    return ids;
}



/*Cell::~Cell()
{
    //dtor
}*/
