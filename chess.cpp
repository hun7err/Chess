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

int Figure::move(Pos newPos) {// to edit
    if(checkMove(newPos)) {
        Hist_rec To_add;
        To_add.Position_before = curPos;

        this->curPos.x = newPos.x;
        this->curPos.y = newPos.y;

        To_add.Position_after = newPos;

        this->fig_hist.push_back(To_add);
        return true;
    } else return false;
}

int Figure::getVal() {
    return val;
}

bool Figure::changeType(int newType){
    if( no==PAWN )
        if ( curPos.y==0 || curPos.y==7 )
            if ( newType==ROOK || newType==BISHOP || newType==KNIGHT || newType==QUEEN ){
                this->no = newType;
                return true;
            }
    return false;
}

///#######################################

Chess::Chess(){}
Chess::~Chess(){}

bool Chess::new_game(){

    for(int i = 0; i<100; i++){
        Board[i] = NULL;
    }
    for(int i = 0; i<32; i++){
        Board[i+64] = &Set[i];
    }
    History.clear();
    Set[0];


}
