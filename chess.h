#include "includes.h"
#ifndef DEFS_H
    #define DEFS_H

    typedef struct Position {
        short int x;
        short int y;
    } Pos;

#endif // DEFS_H


#ifndef HISTORY_H
    #define HISTORY_H

    typedef struct history_record{
        Pos pos_before,
            pos_after;
        bool other_moved;
        history_record * sec_hist_rec;
    } Hist_rec;


#endif // HISTORY_H


#ifndef FIG_H
    #define FIG_H

    class Figure{
        public:
            int no;  //0-King, 1-Pawn, 2-Rook, 3-Bishop, 4-Knight, 5-Queen
            bool color;
            Pos curPos,
                *kingPos;
            int val;
            list <Hist_rec> fig_hist;
            vector <Pos> possibe_moves();
            bool checkMove(Pos newPos);
            bool checkBoundaries(Pos newPos);
            bool move(Pos newPos);
            short int getVal();
        Figure();
        ~Figure();
    };

#endif // FIG_H

#ifndef CHESS_H
    #define CHESS_H

    struct Chess{
        Figure Set[32];
        vector <Pos> Poss_Moves[16];
        list <Figure*> History;
        Figure * Board[8][8];
    };

#endif // CHESS_H

