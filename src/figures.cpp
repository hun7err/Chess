#include "../include/figures.h"
#include <iostream>
#define ABS(x) ((x) < 0) ? -(x) : x

using std::cout;
using std::endl;

/*
void pisz(Figure *Board[]){
    for(int i=0;i<64;i++){
        if(!(i%8))
            cout<<endl<<(i/8+1)<<"    ";
        if(Board[(i%8)*8+i/8]!=NULL)
            cout<<Board[(i%8)*8+i/8]->no<<""<<Board[(i%8)*8+i/8]->color<<" ";
        else
            cout<<"__ ";
    }
    cout<<endl;
    cout<<"y/x  ";
    for(int i=1;i<9;i++)
        cout<<i<<"  ";
    cout<<endl;
}

Pos NPos( short int x, short int y){
    Pos nPos; nPos.set(x,y);
    return nPos;
}
*/

template <class T> void swap ( T& a, T& b ){
  T c(a); a=b; b=c;
}

Pos::Pos() : x_val(0), y_val(0) {}
Pos::~Pos() {}

int Pos::x() const { return x_val; }
int Pos::y() const { return y_val; }
int Pos::index() const { return x_val*8+y_val; }

Pos::Pos(int _x, int _y) : x_val(_x), y_val(_y) {}
Pos::Pos(const Pos &position) : x_val(position.x()), y_val(position.y()) {}

void Pos::setX(int _x) { x_val = _x; }
void Pos::setY(int _y) { y_val = _y; }
void Pos::set(int _x, int _y) { x_val = _x; y_val = _y; }
void Pos::set(const Pos& position) {
    x_val = position.x();
    y_val = position.y();
}

///########################################

Figure::Figure(){}
Figure::~Figure(){}

bool Figure::checkMove(Pos newPos) {
    return this->checkBoundaries(newPos);
}

bool Figure::checkBoundaries(const Pos& newPos) {
    if(newPos.x() < 0 || newPos.x() >= 8 || newPos.y() < 0 || newPos.y() >= 8)
           return false;
    else return true;
}

int Figure::move(Pos newPos) {
    std::cout << "Move" << std::endl;
    if(checkMove(newPos)) {
        this->curPos.set(newPos);
        //this->curPos.x = newPos.x;
        //this->curPos.y = newPos.y;
        return true;
    } else return false;
}

void Figure::setPos(int x, int y) {
    this->curPos.set(x,y);
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
        if ( curPos.y() == 0 || curPos.y() == 7 )
            if ( newType==ROOK || newType==BISHOP || newType==KNIGHT || newType==QUEEN ){
                this->no = newType;
                return true;
            }
    return false;
}

int Figure::ifPossMove( Figure *Board[], bool color, Pos test_Pos, bool _kill, bool _nokill){
    int status = 0;
    King *king = dynamic_cast<King *> (Board[64+color*16]);

    if(!checkBoundaries(test_Pos))
        return 2;

    if(((Board[test_Pos.index()] == NULL)&&(_nokill))||((Board[test_Pos.index()] != NULL)&&((Board[test_Pos.index()]->color != color)&&(_kill)))){
        Figure *help = NULL;
        help = Board[test_Pos.index()];
        Board[test_Pos.index()] = Board[curPos.index()];
        status = king->not_in_danger(Board,color);
        Board[curPos.index()] = Board[test_Pos.index()];
        Board[test_Pos.index()] = help;
        if(help != NULL)
            status+=2;
    }
    return status;
}

///#######################################

Pawn::Pawn(){}
Pawn::~Pawn(){}

vector<Pos> Pawn::possible_moves(Figure *Board[]){
    vector <Pos> PossMoves;
    // 1 Do przodu:
    Pos test_Pos(curPos.x(),curPos.y()+color*(-2)+1);
        if(ifPossMove(Board,color,test_Pos,false)&1)
            PossMoves.push_back(test_Pos);
    // 2 Do przodu:
    if(fig_hist.empty()){
        test_Pos.set(curPos.x(),curPos.y()+color*(-4)+2);
            if(ifPossMove(Board,color,test_Pos,false)&1)
                PossMoves.push_back(test_Pos);
    }
    // bicia
    test_Pos.set(curPos.x()+1,curPos.y()+color*(-2)+1);
        if(ifPossMove(Board,color,test_Pos,true,false)&1)
            PossMoves.push_back(test_Pos);

    test_Pos.set(curPos.x()-1,curPos.y()+color*(-2)+1);
        if(ifPossMove(Board,color,test_Pos,true,false)&1)
            PossMoves.push_back(test_Pos);


    Figure *currFig, *help, *help2, *tested_Pos, *kill_Fig;
    currFig = Board[curPos.x()*8+curPos.y()];
    Board[curPos.x()*8+curPos.y()] = NULL;
    King *king = dynamic_cast<King *> (Board[64+color*16]);    // bicia w przelocie
    test_Pos.set(curPos.x()+1,curPos.y()+color*(-2)+1);
    if(checkBoundaries(test_Pos)==true)
        if(curPos.y()+color == 4){
            kill_Fig = Board[(curPos.x()+1)*8+curPos.y()];
            tested_Pos = Board[(curPos.x()+1)*8+curPos.y()+color*(-2)+1];
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

    test_Pos.set(curPos.x()-1,curPos.y()+color*(-2)+1);
    if(checkBoundaries(test_Pos)==true)
        if(curPos.y()+color == 4){
            kill_Fig = Board[(curPos.x()-1)*8+curPos.y()];
            tested_Pos = Board[(curPos.x()-1)*8+curPos.y()+color*(-2)+1];
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
    Board[curPos.x()*8+curPos.y()] = currFig;

    return PossMoves;
}

///########################################

Queen::Queen(){}
Queen::~Queen(){}

vector<Pos> Queen::possible_moves(Figure *Board[]){
    vector <Pos> PossMoves;
    Pos test_Pos;
    /*
        012
        3X5 <-obrot zgodnie ze schematem
        678
    */
    for(int z=0; z<9; z++){
        if(z==4)
            continue;
        for(int i = 1; i < 8; i++){
            test_Pos.set(curPos.x()+i*(z/3-1),curPos.y()+i*(z%3-1));

            int status = ifPossMove(Board,color,test_Pos);

            if(status&1)
                PossMoves.push_back(test_Pos);
            if(status&2)
                break;
        }
    }

    return PossMoves;
}

///########################################

Rook::Rook(){}
Rook::~Rook(){}

vector <Pos> Rook::possible_moves(Figure *Board[]){
    vector <Pos> PossMoves;
    Pos test_Pos;
    /*
        X1X
        3X5 <-obrot zgodnie ze schematem
        X7X
    */
    for(int z=1; z<9; z+=2){
        for(int i = 1; i < 8; i++){
            test_Pos.set(curPos.x()+i*(z/3-1),curPos.y()+i*(z%3-1));

            int status = ifPossMove(Board,color,test_Pos);

            if(status&1)
                PossMoves.push_back(test_Pos);
            if(status&2)
                break;
        }
    }
    return PossMoves;
}

///########################################

Bishop::Bishop(){}
Bishop::~Bishop(){}

vector <Pos>Bishop::possible_moves(Figure *Board[]){
    vector <Pos> PossMoves;
    Pos test_Pos;
    /*
        0X2
        XXX <-obrot zgodnie ze schematem
        6X8
    */
    for(int z=0; z<9; z+=2){
        if(z==4)
            continue;
        for(int i = 1; i < 8; i++){
            test_Pos.set(curPos.x()+i*(z/3-1),curPos.y()+i*(z%3-1));

            int status = ifPossMove(Board,color,test_Pos);

            if(status&1)
                PossMoves.push_back(test_Pos);
            if(status&2)
                break;
        }
    }
    return PossMoves;
}

///########################################

Knight::Knight(){}
Knight::~Knight(){}

vector<Pos> Knight::possible_moves(Figure *Board[]){
    int kn_mvs[8][2]={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
    vector <Pos> PossMoves;
    Pos test_Pos;

    for(int i=0;i<8;i++){
        test_Pos.set(curPos.x()+kn_mvs[i][0],curPos.y()+kn_mvs[i][1]);

            if(ifPossMove(Board,color,test_Pos)&1)
                PossMoves.push_back(test_Pos);
    }

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
    currFig = Board[curPos.x()*8+curPos.y()];
    Board[curPos.x()*8+curPos.y()] = NULL;

    for(int i=0;i<9;i++){
        if(i==4)
            continue;

        test_Pos.set(prevPos.x()+i/3-1,prevPos.y()+i%3-1);
        if(checkBoundaries(test_Pos)==false)
            continue;

        tested_Pos = Board[(prevPos.x()+i/3-1)*8+prevPos.y()+i%3-1];

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
       tested_Pos = Board[0*8+prevPos.y()];
        if(tested_Pos!=NULL)
            if(tested_Pos->fig_hist.empty())
                if(Board[1*8+prevPos.y()]==NULL&&Board[2*8+prevPos.y()]==NULL&&Board[3*8+prevPos.y()]==NULL){
                    swap(Board[0*8+prevPos.y()],Board[3*8+prevPos.y()]);
                    swap(Board[4*8+prevPos.y()],Board[2*8+prevPos.y()]);
                    curPos.setX(2);

                    if(king->not_in_danger(Board,color)==true)
                        PossMoves.push_back(curPos);

                    swap(Board[0*8+prevPos.y()],Board[3*8+prevPos.y()]);
                    swap(Board[4*8+prevPos.y()],Board[2*8+prevPos.y()]);
                    curPos.setX(4);

                }
        tested_Pos = Board[7*8+(prevPos.y())];
        if(tested_Pos!=NULL)
            if(tested_Pos->fig_hist.empty())
                if(Board[5*8+prevPos.y()]==NULL&&Board[6*8+prevPos.y()]==NULL){
                    swap(Board[7*8+prevPos.y()],Board[5*8+prevPos.y()]);
                    swap(Board[4*8+prevPos.y()],Board[6*8+prevPos.y()]);
                    curPos.setX(6);

                    if(king->not_in_danger(Board,color)==true)
                        PossMoves.push_back(curPos);

                    swap(Board[7*8+prevPos.y()],Board[5*8+prevPos.y()]);
                    swap(Board[4*8+prevPos.y()],Board[6*8+prevPos.y()]);
                    curPos.setX(4);
                }
    }

    Board[prevPos.x()*8+prevPos.y()] = currFig;

    curPos = prevPos;

    return PossMoves;
}

bool King::not_in_danger( Figure *Board[], bool color){
    Pos test_Pos,
        cP = Board[64+color*16]->curPos;
    //Figure *tested_Pos;

    for(int i=0;i<9;i++){ // if other king
        test_Pos.set(cP.x()+i/3-1,cP.y()+i%3-1);
        if(checkBoundaries(test_Pos)==true)
            if(Board[(cP.x()+i/3-1)*8+cP.y()+i%3-1]!=NULL)
                if(Board[(cP.x()+i/3-1)*8+cP.y()+i%3-1]->color!=color&&Board[(cP.x()+i/3-1)*8+cP.y()+i%3-1]->no==KING)
                    return false;
    }

    int kn_mvs[8][2]={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
    for(int i = 0; i < 8; i++){ // if knights
        test_Pos.set(cP.x()+kn_mvs[i][0],cP.y()+kn_mvs[i][1]);
        if(checkBoundaries(test_Pos)==true)
            if(Board[(cP.x()+kn_mvs[i][0])*8+cP.y()+kn_mvs[i][1]]!=NULL)
                if(Board[(cP.x()+kn_mvs[i][0])*8+cP.y()+kn_mvs[i][1]]->color!=color&&Board[(cP.x()+kn_mvs[i][0])*8+cP.y()+kn_mvs[i][1]]->no==KNIGHT)
                    return false;
    }

    for(int z=1;z<9;z+=2){ // Q+R
        for(int i=1;i<7;i++){
            test_Pos.set(cP.x()+i*(z/3-1),cP.y()+i*(z%3-1));
            if(checkBoundaries(test_Pos)==true) {
                if(Board[(cP.x()+i*(z/3-1))*8+cP.y()+i*(z%3-1)]!=NULL) {
                    if(Board[(cP.x()+i*(z/3-1))*8+cP.y()+i*(z%3-1)]->color!=color&&
                       (Board[(cP.x()+i*(z/3-1))*8+cP.y()+i*(z%3-1)]->no==ROOK||Board[(cP.x()+i*(z/3-1))*8+cP.y()+i*(z%3-1)]->no==QUEEN)) {
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
            test_Pos.set(cP.x()+i*(z/3-1),cP.y()+i*(z%3-1));
            if(checkBoundaries(test_Pos)==true) {
                if(Board[(cP.x()+i*(z/3-1))*8+cP.y()+i*(z%3-1)]!=NULL) {
                    if(Board[(cP.x()+i*(z/3-1))*8+cP.y()+i*(z%3-1)]->color!=color&&
                       (Board[(cP.x()+i*(z/3-1))*8+cP.y()+i*(z%3-1)]->no==BISHOP||Board[(cP.x()+i*(z/3-1))*8+cP.y()+i*(z%3-1)]->no==QUEEN)) {
                        return false;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    test_Pos.set(cP.x()+1,cP.y()+1-color*2);
    if(checkBoundaries(test_Pos)==true)
        if(Board[(cP.x()+1)*8+cP.y()+1-color*2]!=NULL)
            if(Board[(cP.x()+1)*8+cP.y()+1-color*2]->color!=color&&Board[(cP.x()+1)*8+cP.y()+1-color*2]->no==PAWN)
                return false;

    test_Pos.set(cP.x()-1,cP.y()+1-color*2);
    if(checkBoundaries(test_Pos)==true)
        if(Board[(cP.x()-1)*8+cP.y()+1-color*2]!=NULL)
            if(Board[(cP.x()-1)*8+cP.y()+1-color*2]->color!=color&&Board[(cP.x()-1)*8+cP.y()+1-color*2]->no==PAWN)
                return false;


    return true;
}

