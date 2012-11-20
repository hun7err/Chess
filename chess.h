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
            Position_after;
        bool Other_figure_moved,
             Other_figure_killed,
             promoted;
        int Other_F_ind;
    } Hist_rec;


#endif // HISTORY_H

#ifndef FIG_H
    #define FIG_H

    class Figure{
        public:
            int no,         // 0-King, 1-Pawn, 2-Rook, 3-Bishop, 4-Knight, 5-Queen
                index;      // in Set[] table
            bool color;     // 0-white, 1-black
            bool alive;
            Pos curPos;
            int val;
            stack <Hist_rec> fig_hist;

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
        vector <Pos> Poss_Moves;
        stack <Figure*> History;
        bool curr_color;
        Figure * Board[100]; // ind 0-63 <- board
                             // ind 64-95 <- pointers to Set
                             // ind 99 <- pointer to History.top() - used for "en passant"
    Chess();
    ~Chess();
    bool new_game();
    bool move(Pos oldPos, Pos newPos);
    bool changeType(Pos curPos, int newType);//to do
    bool undo(); // to do
    vector <Pos> figures_to_move();
    vector <Pos> poss_moves(Pos figPos);
    };

#endif // CHESS_H

