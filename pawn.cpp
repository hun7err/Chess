#include "pawn.h"
#define ABS(x) ((x) < 0) ? -(x) : x

Pawn::Pawn(Pos pos) {
    this->curPos.x = pos.x;
    this->curPos.y = pos.y;
}

Pawn::~Pawn(){}

bool Pawn::checkMove(Pos newPos) {
    if(checkBoundaries(newPos)) {
        if(ABS(newPos.y-curPos.y) == 1 && newPos.x == curPos.x /* && pole_na_newPos_puste */)
            return true;
        else
            return false;
    } else return false;
}
