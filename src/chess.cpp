#include "../include/chess.h"

Chess::Chess(){
    playing = false;
    this->new_game();
}
Chess::~Chess(){}

bool Chess::new_game(){
    int Kind[]= {KING,QUEEN,BISHOP,BISHOP,KNIGHT,KNIGHT,ROOK,ROOK,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN},
        fval[]={13,9,3,3,3,3,5,5,1,1,1,1,1,1,1,1},
        pos_x[]={4,3,2,5,1,6,0,7},
        pos_y[]={0,1,7,6};

    for(int i = 0; i<100; i++){
        Board[i] = NULL;
    }
    for(int i = 0; i<32; i++){
        if(Kind[i/16]==KING){
            King *king = new King();
            Set[i] = dynamic_cast<Figure *> (king);
        }
        else if(Kind[i/16]==QUEEN){
            Queen *queen = new Queen();
            Set[i] = dynamic_cast<Figure *> (queen);
        }
        else if(Kind[i/16]==KNIGHT){
            Knight *knight = new Knight();
            Set[i] = dynamic_cast<Figure *> (knight);
        }
        else if(Kind[i/16]==BISHOP){
            Bishop *bishop = new Bishop();
            Set[i] = dynamic_cast<Figure *> (bishop);
        }
        else if(Kind[i/16]==ROOK){
            Rook *rook = new Rook();
            Set[i] = dynamic_cast<Figure *> (rook);
        }
        else{
            Pawn *pawn = new Pawn();
            Set[i] = dynamic_cast<Figure *> (pawn);
        }
        Board[i+64] = Set[i];
        Set[i]->index = i;
        Set[i]->color = i/16;
        Set[i]->no = Kind[i%16];
        Set[i]->curPos.x = pos_x[i%8];
        Set[i]->curPos.y = pos_y[i/8];
        // a small improvement of the inprovement, no need of other if()s - there was a small bug here overwriting 0. and 7. line of board
        Set[i]->val = fval[i%16];
        Set[i]->alive = true;
        int currPos = Set[i]->curPos.x*8+Set[i]->curPos.y;
        Board[currPos] = Set[i];
    }

    while(!History.empty())
        History.pop();
    curr_color = false;
    playing = true;

    return true;
}

vector <Pos> Chess::figures_to_move(){
    vector <Pos> ret,
                 check;

    for(int i=0; i<16; i++){
        if(!Set[i]->alive)
            continue;

        check = Set[i]->possible_moves(Board);

        if(!check.empty())
            ret.push_back(Set[i]->curPos);
    }
    return ret;
}

vector <Pos> Chess::poss_moves(Pos figPos){
    if(Board[figPos.x*8+figPos.y]!=NULL)
        return Board[figPos.x*8+figPos.y]->possible_moves(Board);
    vector<Pos> nic;
    return nic;
}

int Chess::move(Pos oldPos, Pos newPos){
    Hist_rec rec;
    rec.Other_figure_moved = false;
    rec.Other_figure_killed = false;
    rec.promoted = false;
    rec.Other_F_ind = -1;
    Board[99]=Board[newPos.x*8+newPos.y];
    Figure *tmp = Board[oldPos.x*8+oldPos.y];
    rec.Position_before = tmp->curPos;

    if(Board[newPos.x*8+newPos.y]!=NULL){ // bicie
        rec.Other_figure_killed = true;
        rec.Other_F_ind = Board[newPos.x*8+newPos.y]->index;
        Set[rec.Other_F_ind]->alive = false;
    }
    else if(tmp->no==PAWN && oldPos.x!=newPos.x){ // bicie w przelocie
        rec.Other_figure_killed = true;
        rec.Other_F_ind = Board[newPos.x*8+oldPos.y]->index;
        Board[newPos.x*8+oldPos.y] = NULL;
        Set[rec.Other_F_ind]->alive = false;
    }
    else if(tmp->no==KING && ABS(oldPos.x-newPos.x)==2){ // roszady
        rec.Other_figure_moved = true;
        if(newPos.x==2){
            rec.Other_F_ind = Board[0*8+oldPos.y]->index;
            Set[rec.Other_F_ind]->curPos.x = 3;
            Board[0*8+oldPos.y] = NULL;
            Board[3*8+oldPos.y] = Set[rec.Other_F_ind];
        }
        else{
            rec.Other_F_ind = Board[7*8+oldPos.y]->index;
            Set[rec.Other_F_ind]->curPos.x = 5;
            Board[7*8+oldPos.y] = NULL;
            Board[5*8+oldPos.y] = Set[rec.Other_F_ind];
        }
    }
    if(tmp->no==PAWN && (newPos.y==0 || newPos.y==7)){ // promocja
        rec.promoted = true;
    }
    if(!tmp->move(newPos)) return 0;
    Board[newPos.x*8+newPos.y] = tmp;
    Board[oldPos.x*8+oldPos.y] = NULL;
    rec.Position_after = tmp->curPos;
    tmp->fig_hist.push(rec);
    History.push(tmp);

    if(curr_color) curr_color = false;
    else curr_color = true;

    if(rec.promoted) return 2;
    else return 1;
}

bool Chess::undo(){
    if(History.empty()) return false;
    Hist_rec rec = History.top()->fig_hist.top();
    History.pop();
    Figure *tmp = Board[rec.Position_after.x*8+rec.Position_after.y];
    Board[rec.Position_after.x*8+rec.Position_after.y] = NULL;
    tmp->move(rec.Position_before);

    if(rec.Other_figure_killed){ // bicie
        Set[rec.Other_F_ind]->alive = true;
        Board[Set[rec.Other_F_ind]->curPos.x*8+Set[rec.Other_F_ind]->curPos.y] = Set[rec.Other_F_ind];
    }
    else if(rec.Other_figure_moved){ // roszady
        if(rec.Position_before.x==2){
            Set[rec.Other_F_ind]->curPos.x = 0;
            Board[3*8+rec.Position_before.y] = NULL;
            Board[0*8+rec.Position_before.y] = Set[rec.Other_F_ind];
        }
        else{
            Set[rec.Other_F_ind]->curPos.x = 7;
            Board[5*8+rec.Position_before.y] = NULL;
            Board[7*8+rec.Position_before.y] = Set[rec.Other_F_ind];
        }
    }
    if(rec.promoted){ // promocja
        tmp->no = 0;
    }

    if(curr_color) curr_color = false;
    else curr_color = true;

    return true;

}

bool Chess::changeType(Pos curPos, int newType){
    return Board[curPos.x*8+curPos.y]->changeType(newType);
}


