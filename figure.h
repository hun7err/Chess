#ifndef FIGURE_H
#define FIGURE_H
#include "defs.h"

class Figure {
    private:
        Pos curPos;
        short int val;
    public:
        virtual bool checkMove(Pos newPos);
        bool checkBoundaries(Pos newPos);
        bool move(Pos newPos);
        short int getVal();
    Figure();
    ~Figure();
};

#endif // FIGURE_H
