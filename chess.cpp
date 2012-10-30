#include "chess.h"

Figure::Figure(){}
Figure::~Figure(){}


bool Figure::checkMove(Pos newPos) {
    return this->checkBoundaries(newPos);
}

bool Figure::checkBoundaries(Pos newPos) {
    if(newPos.x < 0 || newPos.x >= 8 || newPos.y < 0 || newPos.y >= 8)
           return false;
    else return true;
}

bool Figure::move(Pos newPos) {
    if(checkMove(newPos)) {
        Hist_rec To_add;
        To_add.pos_before = curPos;

        this->curPos.x = newPos.x;
        this->curPos.y = newPos.y;

        To_add.pos_after = newPos;

        this->fig_hist.push_back(To_add);
        return true;
    } else return false;
}

short int Figure::getVal() {
    return val;
}
