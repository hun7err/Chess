#include "figures.h"

#ifndef CHESS_H
    #define CHESS_H

    class Chess{
        Figure Set[32];
        vector <Pos> Poss_Moves;
        stack <Figure*> History;
        bool curr_color;
        Figure * Board[100]; // ind 0-63 <- board
                             // ind 64-95 <- pointers to Set
                             // ind 99 <- pointer to History.top() - used for "en passant"
    Chess();
    ~Chess();
    bool new_game();
    int move(Pos oldPos, Pos newPos); // 0-ERROR; 1-MOVED; 2-MOVED & NEED CHANGE PAWN TYPE
    bool changeType(Pos curPos, int newType);
    bool undo();
    vector <Pos> figures_to_move();
    vector <Pos> poss_moves(Pos figPos);
    };

#endif // CHESS_H

