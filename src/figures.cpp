#include "../include/figures.h"
#include <iostream>
#define ABS(x) ((x) < 0) ? -(x) : x

template <class T> void swap ( T& a, T& b ){
  T c(a); a=b; b=c;
}

Pos NPos( short int x, short int y){
    Pos nPos; nPos.x=x; nPos.y=y;
    return nPos;
}

///########################################

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

void Figure::setPos(int x, int y) {
    this->curPos.x = x;
    this->curPos.y = y;
}

vector <Pos> Figure::possible_moves(Figure * Board[]) {
    std::cout << "possible_moves z Figure" << std::endl;
    vector<Pos> ret;
    return ret;
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

Pawn::Pawn(){}
Pawn::~Pawn(){}

vector<Pos> Pawn::possible_moves(Figure *Board[]){
    vector <Pos> PossMoves;
    Pos test_Pos;
    Figure *currFig, *help, *help2, *tested_Pos, *kill_Fig;
    currFig = Board[curPos.x*8+curPos.y];
    Board[curPos.x*8+curPos.y] = NULL;
    King *king = dynamic_cast<King *> (Board[64+color*16]);
    // 1 Do przodu:
    test_Pos = NPos(curPos.x,curPos.y+color*(-2)+1);
    if(checkBoundaries(test_Pos)==true){
        tested_Pos = Board[curPos.x*8+curPos.y+color*(-2)+1];
        if(tested_Pos==NULL){
            tested_Pos = currFig;
            if(king->not_in_danger(Board,color)==true){
                 PossMoves.push_back(test_Pos);
            }
            tested_Pos = NULL;

        }
    }
    // 2 Do przodu:
    if(fig_hist.empty()){
        test_Pos = NPos(curPos.x,curPos.y+color*(-4)+2);
        if(checkBoundaries(test_Pos)==true){
            tested_Pos = Board[curPos.x*8+curPos.y+color*(-4)+2];
            if(tested_Pos==NULL){
                tested_Pos = currFig;

                if(king->not_in_danger(Board,color)==true)
                     PossMoves.push_back(test_Pos);

                tested_Pos = NULL;

            }
        }
    }
    // bicia
    test_Pos = NPos(curPos.x+1,curPos.y+color*(-2)+1);
    if(checkBoundaries(test_Pos)==true){
        tested_Pos = Board[(curPos.x+1)*8+curPos.y+color*(-2)+1];
        if(tested_Pos!=NULL)
            if(tested_Pos->color != color){
                help = tested_Pos;
                tested_Pos = currFig;

                if(king->not_in_danger(Board,color)==true)
                    PossMoves.push_back(test_Pos);

                tested_Pos = help;

            }
    }
    test_Pos = NPos(curPos.x-1,curPos.y+color*(-2)+1);
    if(checkBoundaries(test_Pos)==true){
        tested_Pos = Board[(curPos.x-1)*8+curPos.y+color*(-2)+1];
        if(tested_Pos!=NULL)
            if(tested_Pos->color != color){
                help = tested_Pos;
                tested_Pos = currFig;

                if(king->not_in_danger(Board,color)==true)
                    PossMoves.push_back(test_Pos);

                tested_Pos = help;

            }
    }
    // bicia w przelocie
    test_Pos = NPos(curPos.x+1,curPos.y+color*(-2)+1);
    if(checkBoundaries(test_Pos)==true)
        if(curPos.y-color == 4){
            kill_Fig = Board[(curPos.x+1)*8+curPos.y];
            tested_Pos = Board[(curPos.x+1)*8+curPos.y+color*(-2)+1];
            if(tested_Pos==NULL)
                if(kill_Fig!=NULL)
                    if(kill_Fig->no==PAWN)
                        if(kill_Fig == Board[99]){
                            help = tested_Pos;
                            help2 = kill_Fig;
                            tested_Pos = currFig;
                            kill_Fig = NULL;

                            if(king->not_in_danger(Board,color)==true)
                                PossMoves.push_back(test_Pos);

                            tested_Pos = help;
                            kill_Fig = help2;
            }
        }

    test_Pos = NPos(curPos.x-1,curPos.y+color*(-2)+1);
    if(checkBoundaries(test_Pos)==true)
        if(curPos.y-color == 4){
            kill_Fig = Board[(curPos.x-1)*8+curPos.y];
            tested_Pos = Board[(curPos.x-1)*8+curPos.y+color*(-2)+1];
            if(tested_Pos==NULL)
                if(kill_Fig!=NULL)
                    if(kill_Fig->no==PAWN)
                        if(kill_Fig == Board[99]){
                            help = tested_Pos;
                            help2 = kill_Fig;
                            tested_Pos = currFig;
                            kill_Fig = NULL;

                            if(king->not_in_danger(Board,color)==true)
                                PossMoves.push_back(test_Pos);

                            tested_Pos = help;
                            kill_Fig = help2;
            }
        }


    Board[curPos.x*8+curPos.y] = currFig;
    return PossMoves;
}

///########################################

Queen::Queen(){}
Queen::~Queen(){}

vector<Pos> Queen::possible_moves(Figure *Board[]){
    vector <Pos> PossMoves;
    Pos test_Pos;
    Figure *currFig, *help, *tested_Pos;
    currFig = Board[curPos.x*8+curPos.y];
    Board[curPos.x*8+curPos.y] = NULL;
    King *king = dynamic_cast<King *> (Board[64+color*16]);
    /*
        012
        3X5 <-obrot zgodnie ze schematem
        678
    */
    for(int z=0; z<9; z++){
        if(z==4)
            continue;
        for(int i = 1; i < 8; i++){
            test_Pos = NPos(curPos.x+i*(z/3-1),curPos.y+i*(z%3-1));

            if(checkBoundaries(test_Pos)==false)
                break;

            tested_Pos = Board[(curPos.x+i*(z/3-1))*8+curPos.y+i*(z%3-1)];

            if(tested_Pos  == NULL){
                tested_Pos = currFig;

                if(king->not_in_danger(Board,color)==true)
                    PossMoves.push_back(test_Pos);

                tested_Pos = NULL;
            }
            else if(tested_Pos->color != color){ //jeżeli mialoby byc bicie
                help = tested_Pos;
                tested_Pos = currFig;

                if(king->not_in_danger(Board,color)==true)
                    PossMoves.push_back(test_Pos);

                tested_Pos = help;
                break;
            }
            else break;
        }
    }

    Board[curPos.x*8+curPos.y] = currFig;

    return PossMoves;
}

///########################################

Rook::Rook(){}
Rook::~Rook(){}

vector <Pos> Rook::possible_moves(Figure *Board[]){
    vector <Pos> PossMoves;
    Pos test_Pos;
    Figure *currFig, *help, *tested_Pos;
    currFig = Board[curPos.x*8+curPos.y];
    Board[curPos.x*8+curPos.y] = NULL;
    King *king = dynamic_cast<King *> (Board[64+color*16]);
    /*
        X1X
        3X5 <-obrot zgodnie ze schematem
        X7X
    */
    for(int z=1; z<9; z+=2){
        for(int i = 1; i < 8; i++){
            test_Pos = NPos(curPos.x+i*(z/3-1),curPos.y+i*(z%3-1));

            if(checkBoundaries(test_Pos)==false)
                break;

            tested_Pos = Board[(curPos.x+i*(z/3-1))*8+curPos.y+i*(z%3-1)];

            if(tested_Pos  == NULL){
                tested_Pos = currFig;

                if(king->not_in_danger(Board,color)==true)
                    PossMoves.push_back(test_Pos);

                tested_Pos = NULL;
            }
            else if(tested_Pos->color != color){ //jeżeli mialoby byc bicie
                help = tested_Pos;
                tested_Pos = currFig;

                if(king->not_in_danger(Board,color)==true)
                    PossMoves.push_back(test_Pos);

                tested_Pos = help;
                break;
            }
            else break;
        }
    }

    Board[curPos.x*8+curPos.y] = currFig;

    return PossMoves;
}

///########################################

Bishop::Bishop(){}
Bishop::~Bishop(){}

vector <Pos>Bishop::possible_moves(Figure *Board[]){
    vector <Pos> PossMoves;
    Pos test_Pos;
    Figure *currFig, *help, *tested_Pos;
    currFig = Board[curPos.x*8+curPos.y];
    Board[curPos.x*8+curPos.y] = NULL;
    King *king = dynamic_cast<King *> (Board[64+color*16]);
    /*
        0X2
        XXX <-obrot zgodnie ze schematem
        6X8
    */
    for(int z=0; z<9; z+=2){
        if(z==4)
            continue;
        for(int i = 1; i < 8; i++){
            test_Pos = NPos(curPos.x+i*(z/3-1),curPos.y+i*(z%3-1));

            if(checkBoundaries(test_Pos)==false)
                break;

            tested_Pos = Board[(curPos.x+i*(z/3-1))*8+curPos.y+i*(z%3-1)];

            if(tested_Pos  == NULL){
                tested_Pos = currFig;

                if(king->not_in_danger(Board,color)==true)
                    PossMoves.push_back(test_Pos);

                tested_Pos = NULL;
            }
            else if(tested_Pos->color != color){ //jeżeli mialoby byc bicie
                help = tested_Pos;
                tested_Pos = currFig;

                if(king->not_in_danger(Board,color)==true)
                    PossMoves.push_back(test_Pos);

                tested_Pos = help;
                break;
            }
            else break;
        }
    }

    Board[curPos.x*8+curPos.y] = currFig;

    return PossMoves;
}

///########################################

Knight::Knight(){}
Knight::~Knight(){}

vector<Pos> Knight::possible_moves(Figure *Board[]){
    int kn_mvs[8][2]={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
    vector <Pos> PossMoves;
    Pos test_Pos;
    Figure *currFig, *help, *tested_Pos;
    currFig = Board[curPos.x*8+curPos.y];
    Board[curPos.x*8+curPos.y] = NULL;
    King *king = dynamic_cast<King *> (Board[64+color*16]);

    for(int i=0;i<8;i++){
        test_Pos = NPos(curPos.x+kn_mvs[i][0],curPos.y+kn_mvs[i][1]);
        if(checkBoundaries(test_Pos)==false)
            continue;

        tested_Pos = Board[(curPos.x+kn_mvs[i][0])*8+curPos.y+kn_mvs[i][1]];

        if(tested_Pos==NULL){
            tested_Pos = currFig;

            if(king->not_in_danger(Board,color)==true)
                PossMoves.push_back(test_Pos);

            tested_Pos = NULL;
        }
        else if(tested_Pos->color!=color){
            help = tested_Pos;
            tested_Pos = currFig;

            if(king->not_in_danger(Board,color)==true)
                PossMoves.push_back(test_Pos);

            tested_Pos = help;
        }
    }

    Board[curPos.x*8+curPos.y] = currFig;

    return PossMoves;
}

///########################################

King::King(){}
King::~King(){}

vector<Pos> King::possible_moves(Figure *Board[]){
    King *king = dynamic_cast<King *> (Board[64+color*16]);
    bool if_not_danger = king->not_in_danger(Board,color);
    vector <Pos> PossMoves;
    Pos test_Pos, prevPos = curPos;
    Figure *currFig, *help, /* *help2,*/ *tested_Pos;
    currFig = Board[curPos.x*8+curPos.y];
    Board[curPos.x*8+curPos.y] = NULL;

    for(int i=0;i<9;i++){
        if(i==4)
            continue;

        test_Pos = NPos(prevPos.x+i/3-1,prevPos.y+i%3-1);
        if(checkBoundaries(test_Pos)==false)
            continue;

        tested_Pos = Board[(prevPos.x+i/3-1)*8+prevPos.y+i%3-1];

        if(tested_Pos==NULL){
            tested_Pos = currFig;
            curPos = test_Pos;
            if(king->not_in_danger(Board,color)==true)
                PossMoves.push_back(test_Pos);
            tested_Pos = NULL;
        }
        else if(tested_Pos->color!=color){
            help = tested_Pos;
            tested_Pos = currFig;
            curPos = test_Pos;
            if(king->not_in_danger(Board,color)==true)
                PossMoves.push_back(test_Pos);
            tested_Pos = help;
        }
    }

    if(if_not_danger&&fig_hist.empty()){ //ROSZADY
       tested_Pos = Board[0*8+prevPos.y];
        if(tested_Pos!=NULL)
            if(tested_Pos->fig_hist.empty())
                if(Board[1*8+prevPos.y]==NULL&&Board[2*8+prevPos.y]==NULL&&Board[3*8+prevPos.y]==NULL){
                    swap(Board[0*8+prevPos.y],Board[3*8+prevPos.y]);
                    swap(Board[4*8+prevPos.y],Board[2*8+prevPos.y]);
                    curPos.x = 2;

                    if(king->not_in_danger(Board,color)==true)
                        PossMoves.push_back(curPos);

                    swap(Board[0*8+prevPos.y],Board[3*8+prevPos.y]);
                    swap(Board[4*8+prevPos.y],Board[2*8+prevPos.y]);
                    curPos.x = 4;

                }
        tested_Pos = Board[7*8+(prevPos.y)];
        if(tested_Pos!=NULL)
            if(tested_Pos->fig_hist.empty())
                if(Board[5*8+prevPos.y]==NULL&&Board[6*8+prevPos.y]==NULL){
                    swap(Board[7*8+prevPos.y],Board[5*8+prevPos.y]);
                    swap(Board[4*8+prevPos.y],Board[6*8+prevPos.y]);
                    curPos.x = 6;

                    if(king->not_in_danger(Board,color)==true)
                        PossMoves.push_back(curPos);

                    swap(Board[7*8+prevPos.y],Board[5*8+prevPos.y]);
                    swap(Board[4*8+prevPos.y],Board[6*8+prevPos.y]);
                    curPos.x = 4;
                }
    }

    Board[prevPos.x*8+prevPos.y] = currFig;

    curPos = prevPos;

    return PossMoves;
}

bool King::not_in_danger( Figure *Board[], bool color){
    Pos test_Pos,
        cP = Board[64+color*16]->curPos;
    //Figure *tested_Pos;

    for(int i=0;i<9;i++){ // if other king
        test_Pos = NPos(cP.x+i/3-1,cP.y+i%3-1);
        if(checkBoundaries(test_Pos)==true)
            if(Board[(cP.x+i/3-1)*8+cP.y+i%3-1]!=NULL)
                if(Board[(cP.x+i/3-1)*8+cP.y+i%3-1]->color!=color&&Board[(cP.x+i/3-1)*8+cP.y+i%3-1]->no==KING)
                    return false;
    }

    int kn_mvs[8][2]={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
    for(int i = 0; i < 8; i++){ // if knights
        test_Pos = NPos(cP.x+kn_mvs[i][0],cP.y+kn_mvs[i][1]);
        if(checkBoundaries(test_Pos)==true)
            if(Board[(cP.x+kn_mvs[i][0])*8+cP.y+kn_mvs[i][1]]!=NULL)
                if(Board[(cP.x+kn_mvs[i][0])*8+cP.y+kn_mvs[i][1]]->color!=color&&Board[(cP.x+kn_mvs[i][0])*8+cP.y+kn_mvs[i][1]]->no==KNIGHT)
                    return false;
    }

    for(int z=1;z<9;z+=2){ // Q+R
        for(int i=1;i<7;i++){
            test_Pos = NPos(cP.x+i*(z/3-1),cP.y+i*(z%3-1));
            if(checkBoundaries(test_Pos)==true) {
                if(Board[(cP.x+i*(z/3-1))*8+cP.y+i*(z%3-1)]!=NULL) {
                    if(Board[(cP.x+i*(z/3-1))*8+cP.y+i*(z%3-1)]->color!=color&&
                       (Board[(cP.x+i*(z/3-1))*8+cP.y+i*(z%3-1)]->no==ROOK||Board[(cP.x+i*(z/3-1))*8+cP.y+i*(z%3-1)]->no==QUEEN)) {
                        return false;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    for(int z=0;z<9;z+=2){ //Q+B
        if(z==4)
            continue;
        for(int i=1;i<7;i++){
            test_Pos = NPos(cP.x+i*(z/3-1),cP.y+i*(z%3-1));
            if(checkBoundaries(test_Pos)==true) {
                if(Board[(cP.x+i*(z/3-1))*8+cP.y+i*(z%3-1)]!=NULL) {
                    if(Board[(cP.x+i*(z/3-1))*8+cP.y+i*(z%3-1)]->color!=color&&
                       (Board[(cP.x+i*(z/3-1))*8+cP.y+i*(z%3-1)]->no==BISHOP||Board[(cP.x+i*(z/3-1))*8+cP.y+i*(z%3-1)]->no==QUEEN)) {
                        return false;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    test_Pos = NPos(cP.x+1,cP.y+1-color*2);
    if(checkBoundaries(test_Pos)==true)
        if(Board[(cP.x+1)*8+cP.y+1-color*2]!=NULL)
            if(Board[(cP.x+1)*8+cP.y+1-color*2]->color!=color&&Board[(cP.x+1)*8+cP.y+1-color*2]->no==PAWN)
                return false;

    test_Pos = NPos(cP.x-1,cP.y+1-color*2);
    if(checkBoundaries(test_Pos)==true)
        if(Board[(cP.x-1)*8+cP.y+1-color*2]!=NULL)
            if(Board[(cP.x-1)*8+cP.y+1-color*2]->color!=color&&Board[(cP.x-1)*8+cP.y+1-color*2]->no==PAWN)
                return false;


    return true;
}

