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
        Pos Position_before,
            Position_after,
            Other_F_Pos_before,
            Other_F_Pos_after;
        bool Other_figure_moved;
    } Hist_rec;


#endif // HISTORY_H

#ifndef FIG_H
    #define FIG_H

    class Figure{
        public:
            int no,         // 0-King, 1-Pawn, 2-Rook, 3-Bishop, 4-Knight, 5-Queen
                index;      // in Set[] table
            bool color;     // 0-white, 1-black
            Pos curPos;
            int val;
            list <Hist_rec> fig_hist;
            virtual vector <Pos> possible_moves();
            bool checkMove(Pos newPos);
            bool checkBoundaries(Pos newPos);
            int move(Pos newPos);
            bool changeType(int newType);
            int getVal();
        Figure();
        ~Figure();
    };

#endif // FIG_H

#ifndef CHESS_H
    #define CHESS_H

    class Chess{
        Figure Set[32];
        vector <Pos> Poss_Moves[16];
        list <Figure*> History;
        Figure * Board[100]; // ind 0-63 <- board
                             // ind 64-95 <- pointers to Set
                             // ind 99 <- pointer to History.top() - used for "en passant"
    bool new_game();
    bool undo();
    bool move(Pos oldPos, Pos newPos);
    Chess();
    ~Chess();
    };

#endif // CHESS_H

