#include "chess.h"
#include "figures.h"

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

int Figure::move(Pos newPos) {
    if(checkMove(newPos)) {
        this->curPos.x = newPos.x;
        this->curPos.y = newPos.y;
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

Chess::Chess(){
    this->new_game();
}
Chess::~Chess(){}

bool Chess::new_game(){
    int kind[]= {KING,QUEEN,BISHOP,BISHOP,KNIGHT,KNIGHT,ROOK,ROOK,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN},
        fval[]={13,9,3,3,3,3,5,5,1,1,1,1,1,1,1,1},
        pos_x[]={4,3,2,5,1,6,0,7},
        pos_y[]={0,7};

    for(int i = 0; i<100; i++){
        Board[i] = NULL;
    }
    for(int i = 0; i<32; i++){
        Board[i+64] = &Set[i];
        Set[i].index = i;
        Set[i].color = i/16;
        Set[i].no = kind[i%16];
        Set[i].curPos.x = pos_x[i%8];
        Set[i].curPos.y = pos_y[i/16];
        Set[i].val = fval[i%16];
        Set[i].alive = true;
        int currPos = Set[i].curPos.x*8+Set[i].curPos.y;
        Board[currPos] = &Set[i];

    }
    while(!History.empty())
        History.pop();
    curr_color = 0;

    return true;
}

vector <Pos> Chess::figures_to_move(){
    vector <Pos> ret,
                 check;

    for(int i=0; i<16; i++){
        if(!Set[i].alive)
            continue;
        if(Set[i].no==KING){
            King *king = dynamic_cast<King *> (&Set[i]);
            check = king->possible_moves(Board);
        }
        else if(Set[i].no==QUEEN){
            Queen *queen = dynamic_cast<Queen *> (&Set[i]);
            check = queen->possible_moves(Board);
        }
        else if(Set[i].no==KNIGHT){
            Knight *knight = dynamic_cast<Knight *> (&Set[i]);
            check = knight->possible_moves(Board);
        }
        else if(Set[i].no==BISHOP){
            Bishop *bishop = dynamic_cast<Bishop *> (&Set[i]);
            check = bishop->possible_moves(Board);
        }
        else if(Set[i].no==ROOK){
            Rook *rook = dynamic_cast<Rook *> (&Set[i]);
            check = rook->possible_moves(Board);
        }
        else{
            Pawn *pawn = dynamic_cast<Pawn *> (&Set[i]);
            check = pawn->possible_moves(Board);
        }
        if(!check.empty())
            ret.push_back(Set[i].curPos);
    }
    return ret;
}

vector <Pos> Chess::poss_moves(Pos figPos){
    if(Board[figPos.x*8+figPos.y])
        if(Board[figPos.x*8+figPos.y]->no==KING){
            King *king = dynamic_cast<King *> (Board[figPos.x*8+figPos.y]);
            return king->possible_moves(Board);
        }
        if(Board[figPos.x*8+figPos.y]->no==QUEEN){
            Queen *queen = dynamic_cast<Queen *> (Board[figPos.x*8+figPos.y]);
            return queen->possible_moves(Board);
        }
        if(Board[figPos.x*8+figPos.y]->no==KNIGHT){
            Knight *knight = dynamic_cast<Knight *> (Board[figPos.x*8+figPos.y]);
            return knight->possible_moves(Board);
        }
        if(Board[figPos.x*8+figPos.y]->no==BISHOP){
            Bishop *bishop = dynamic_cast<Bishop *> (Board[figPos.x*8+figPos.y]);
            return bishop->possible_moves(Board);
        }
        if(Board[figPos.x*8+figPos.y]->no==ROOK){
            Rook *rook = dynamic_cast<Rook *> (Board[figPos.x*8+figPos.y]);
            return rook->possible_moves(Board);
        }
        Pawn *pawn = dynamic_cast<Pawn *> (Board[figPos.x*8+figPos.y]);
        return pawn->possible_moves(Board);

}

bool Chess::move(Pos oldPos, Pos newPos){
    Hist_rec rec;
    rec.Other_figure_moved = false;
    rec.Other_figure_killed = false;
    rec.promoted = false;
    rec.Other_F_ind = -1;

    Figure *tmp = Board[oldPos.x*8+oldPos.y];
    rec.Position_before = tmp->curPos;

    if(Board[newPos.x*8+newPos.y]!=NULL){ // bicie
        rec.Other_figure_killed = true;
        rec.Other_F_ind = Board[newPos.x*8+newPos.y]->index;
        Set[rec.Other_F_ind].alive = false;
    }
    else if(tmp->no==PAWN && oldPos.x!=newPos.x){ // bicie w przelocie
        rec.Other_figure_killed = true;
        rec.Other_F_ind = Board[newPos.x*8+oldPos.y]->index;
        Board[newPos.x*8+oldPos.y] = NULL;
        Set[rec.Other_F_ind].alive = false;
    }
    else if(tmp->no==KING && ABS(oldPos.x-newPos.x)==2){ // roszady
        rec.Other_figure_moved = true;
        if(newPos.x==2){
            rec.Other_F_ind = Board[0*8+oldPos.y]->index;
            Set[rec.Other_F_ind].curPos.x = 3;
            Board[0*8+oldPos.y] = NULL;
            Board[3*8+oldPos.y] = &Set[rec.Other_F_ind];
        }
        else{
            rec.Other_F_ind = Board[7*8+oldPos.y]->index;
            Set[rec.Other_F_ind].curPos.x = 5;
            Board[7*8+oldPos.y] = NULL;
            Board[5*8+oldPos.y] = &Set[rec.Other_F_ind];
        }
    }
    if(tmp->no==PAWN && (newPos.y==0 || newPos.y==7)){ // promocja
        rec.promoted = true;
    }
    if(!tmp->move(newPos)) return false;
    Board[newPos.x*8+newPos.y] = tmp;
    Board[oldPos.x*8+oldPos.y] = NULL;
    rec.Position_after = tmp->curPos;
    tmp->fig_hist.push(rec);
    History.push(tmp);
    return true;
}

bool Chess::undo(){ // to do
    if(History.empty()) return false;
    Hist_rec rec = History.top()->fig_hist.top();
    History.pop();
    Figure *tmp = Board[rec.Position_after.x*8+rec.Position_after.y];
    Board[rec.Position_after.x*8+rec.Position_after.y] = NULL;
    tmp->move(rec.Position_before);

    if(rec.Other_figure_killed){ // bicie
        Set[rec.Other_F_ind].alive = true;
        Board[Set[rec.Other_F_ind].curPos.x*8+Set[rec.Other_F_ind].curPos.y] = &Set[rec.Other_F_ind];
    }
    else if(rec.Other_figure_moved){ // roszady todo
        if(rec.Position_before.x==2){
            Set[rec.Other_F_ind].curPos.x = 0;
            Board[3*8+rec.Position_before.y] = NULL;
            Board[0*8+rec.Position_before.y] = &Set[rec.Other_F_ind];
        }
        else{
            Set[rec.Other_F_ind].curPos.x = 7;
            Board[5*8+rec.Position_before.y] = NULL;
            Board[7*8+rec.Position_before.y] = &Set[rec.Other_F_ind];

        }
    }
    if(rec.promoted){ // promocja
        tmp->no = 0;
    }
    return true;

}

