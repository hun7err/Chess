#include "figure.h"

Figure::Figure(){}
Figure::~Figure(){}

bool Figure::checkBoundaries(Pos newPos) {
    if(newPos.x < 0 || newPos.x >= 8 || newPos.y < 0 || newPos.y >= 8)
           return false;
    else return true;
}

bool Figure::checkMove(Pos newPos) {
    return this->checkBoundaries(newPos);
}

bool Figure::move(Pos newPos) {
    if(checkMove(newPos)) {
        this->curPos.x = newPos.x;
        this->curPos.y = newPos.y;
        return true;
    } else return false;
}

short int Figure::getVal() {
    return val;
}
