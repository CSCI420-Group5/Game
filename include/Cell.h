#ifndef CELL_H
#define CELL_H
#include "vector"

class Cell
{
    public:
        Cell();
        /*virtual ~Cell();*/

        void addID(long int new_id);
        void clearIDs();
        void setStandable(bool boolean);

        bool isStandable();
        std::vector<long int> getIDs();
    protected:
    private:
        std::vector<long int> ids;
        bool standable;
};

#endif // CELL_H
