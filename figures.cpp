#include "figures.h"
#define ABS(x) ((x) < 0) ? -(x) : x


Pos NPos( short int x, short int y){
    Pos nPos; nPos.x=x; nPos.y=y;
    return nPos;
}

///########################################

Pawn::Pawn(Pos pos) {
    this->curPos.x = pos.x;
    this->curPos.y = pos.y;
}

Pawn::~Pawn(){}

///########################################

Queen::Queen(Pos pos) {
    this->curPos.x = pos.x;
    this->curPos.y = pos.y;
}

Queen::~Queen(){}

vector<Pos> Queen::possibe_moves(Figure * Board[8][8]){
    vector <Pos> PossMoves;
    Pos test_Pos;
    Figure *curr, *help;
    curr=Board[curPos.x][curPos.y];
    Board[curPos.x][curPos.y]=NULL;

    for(int z=0; z<9; z++){
        if(z==4)
            continue;
        for(int i=1;i<8;i++){
            test_Pos = NPos(curPos.x+i*(z/3-1),curPos.y+i*(z%3-1));
            if(checkBoundaries(test_Pos)==false)
                break;
            else if(Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]==NULL||Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]->color!=color){
                help=Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)];
                Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]=curr;

                if(King::not_in_danger(Board[8][8],color)==true)
                    PossMoves.push_back(test_Pos);

                Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]=help;
            }
            else break;
        }
    }

    Board[curPos.x][curPos.y]=curr;

    return PossMoves;
}

///########################################

Rook::Rook(Pos pos) {
    this->curPos.x = pos.x;
    this->curPos.y = pos.y;
}

Rook::~Rook(){}

vector <Pos> Rook::possibe_moves(Figure * Board[8][8]){
    vector <Pos> PossMoves;
    Pos test_Pos;
    Figure *curr, *help;
    curr=Board[curPos.x][curPos.y];
    Board[curPos.x][curPos.y]=NULL;

    for(int z=1; z<9; z+=2){
        for(int i=1;i<8;i++){
            test_Pos = NPos(curPos.x+i*(z/3-1),curPos.y+i*(z%3-1));
            if(checkBoundaries(test_Pos)==false)
                break;
            else if(Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]==NULL||Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]->color!=color){
                help=Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)];
                Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]=curr;

                if(King::not_in_danger(Board[8][8],color)==true)
                    PossMoves.push_back(test_Pos);

                Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]=help;
            }
            else break;
        }
    }

    Board[curPos.x][curPos.y]=curr;

    return PossMoves;
}

///########################################

Bishop::Bishop(Pos pos) {
    this->curPos.x = pos.x;
    this->curPos.y = pos.y;
}

Bishop::~Bishop(){}

vector <Pos>Bishop::possibe_moves(Figure * Board[8][8]){
    vector <Pos> PossMoves;
    Pos test_Pos;
    Figure *curr, *help;
    curr=Board[curPos.x][curPos.y];
    Board[curPos.x][curPos.y]=NULL;

    for(int z=0; z<9; z+=2){
        if(z==4)
            continue;
        for(int i=1;i<8;i++){
            test_Pos = NPos(curPos.x+i*(z/3-1),curPos.y+i*(z%3-1));
            if(checkBoundaries(test_Pos)==false)
                break;
            else if(Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]==NULL||Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]->color!=color){
                help=Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)];
                Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]=curr;

                if(King::not_in_danger(Board[8][8],color)==true)
                    PossMoves.push_back(test_Pos);

                Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]=help;
            }
            else break;
        }
    }

    Board[curPos.x][curPos.y]=curr;

    return PossMoves;
}

///########################################

Knight::Knight(Pos pos) {
    this->curPos.x = pos.x;
    this->curPos.y = pos.y;
}

Knight::~Knight(){}

vector<Pos> Knight::possibe_moves(Figure * Board[8][8]){
    int kn_mvs[8][2]={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
    vector <Pos> PossMoves;
    Pos test_Pos;
    Figure *curr, *help;
    curr=Board[curPos.x][curPos.y];
    Board[curPos.x][curPos.y]=NULL;

    for(int i=0;i<8;i++){
        test_Pos = NPos(curPos.x+kn_mvs[i][0],curPos.y+kn_mvs[i][1]);
        if(checkBoundaries(test_Pos)==false)
            break;
        else if(Board[curPos.x+kn_mvs[i][0]][curPos.y+kn_mvs[i][1]]==NULL||Board[curPos.x+kn_mvs[i][0]][curPos.y+kn_mvs[i][1]]->color!=color){
            help=Board[curPos.x+kn_mvs[i][0]][curPos.y+kn_mvs[i][1]];
            Board[curPos.x+kn_mvs[i][0]][curPos.y+kn_mvs[i][1]]=curr;

            if(King::not_in_danger(Board[8][8],color)==true)
                PossMoves.push_back(test_Pos);

            Board[curPos.x+kn_mvs[i][0]][curPos.y+kn_mvs[i][1]]=help;
        }
        else break;
    }

    Board[curPos.x][curPos.y]=curr;

    return PossMoves;
}

///########################################

King::King(Pos pos) {
    this->curPos.x = pos.x;
    this->curPos.y = pos.y;
}

King::~King(){}

vector<Pos> King::possibe_moves(Figure * Board[8][8]){
    vector <Pos> PossMoves;
    Pos test_Pos, prevPos=curPos;
    Figure *curr, *help;
    curr=Board[curPos.x][curPos.y];
    Board[curPos.x][curPos.y]=NULL;

    for(int i=0;i<9;i++){
        if(i==4)
            continue;
        test_Pos = NPos(prevPos.x+i/3-1,prevPos.y+i%3-1);
        if(checkBoundaries(test_Pos)==false)
            break;
        else if(Board[prevPos.x+i/3-1][prevPos.y+i%3-1]==NULL||Board[prevPos.x+i/3-1][prevPos.y+i%3-1]->color!=color){
            help=Board[prevPos.x+i/3-1][prevPos.y+i%3-1];
            Board[prevPos.x+i/3-1][prevPos.y+i%3-1]=curr;

            if(King::not_in_danger(Board[8][8],color)==true)
                PossMoves.push_back(test_Pos);

            Board[prevPos.x+i/3-1][prevPos.y+i%3-1]=help;
        }
        else break;
    }

    /// + roszady

    Board[prevPos.x][prevPos.y]=curr;

    curPos=prevPos;

    return PossMoves;
}

bool King::not_in_danger( Figure * Board[8][8], bool color){
    Pos test_Pos;
    for(int i=0;i<9;i++){ // if other king
        test_Pos = NPos(curPos.x+i/3-1,curPos.y+i%3-1);
        if(checkBoundaries(test_Pos)==true)
            if(Board[curPos.x+i/3-1][curPos.y+i%3-1]!=NULL)
                if(Board[curPos.x+i/3-1][curPos.y+i%3-1]->color!=color&&Board[curPos.x+i/3-1][curPos.y+i%3-1]->no==0)
                    return false;
    }

    test_Pos = NPos(curPos.x+2,curPos.y+1); // if knights
    if(checkBoundaries(test_Pos)==true)
        if(Board[curPos.x+2][curPos.y+1]!=NULL)
            if(Board[curPos.x+2][curPos.y+1]->color!=color&&Board[curPos.x+2][curPos.y+1]->no==4)
                return false;

    for(int z=1;z<9;z+=2){ // Q+R
        for(int i=1;i<7;i++){
            test_Pos = NPos(curPos.x+i*(z/3-1),curPos.y+i*(z%4-1));
            if(checkBoundaries(test_Pos)==true)
                if(Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]!=NULL)
                    if(Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]->color!=color&&(Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]->no==2||Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]->no==5))
                        return false;
                    else
                        break;
        }
    }

    for(int z=0;z<9;z+=2){ //Q+B
        if(z==4)
            continue;
        for(int i=1;i<7;i++){
            test_Pos = NPos(curPos.x+i*(z/3-1),curPos.y+i*(z%4-1));
            if(checkBoundaries(test_Pos)==true)
                if(Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]!=NULL)
                    if(Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]->color!=color&&(Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]->no==3||Board[curPos.x+i*(z/3-1)][curPos.y+i*(z%3-1)]->no==5))
                        return false;
                    else
                        break;
        }
    }

    return true;
}

