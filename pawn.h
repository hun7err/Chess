#ifndef PAWN_H
#define PAWN_H
#include "figure.h"

class Pawn : public Figure {
    public:
        bool checkMove(Pos newPos);
    Pawn(Pos pos);
    ~Pawn();
};

#endif // PAWN_H
