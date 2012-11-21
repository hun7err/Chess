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

#ifndef FIGURES_H
    #define FIGURES_H

    class Pawn : private Figure{
        public:
            vector <Pos> possible_moves(Figure * Board[]);
    Pawn(Pos pos);
    ~Pawn();
    };

    class Queen : private Figure{
        public:
            vector <Pos> possible_moves(Figure * Board[]);
    Queen(Pos pos);
    ~Queen();
    };

    class Rook : private Figure{
        public:
            vector <Pos> possible_moves(Figure * Board[]);
    Rook(Pos pos);
    ~Rook();
    };

    class Bishop : private Figure{
        public:
            vector <Pos> possible_moves(Figure * Board[]);
    Bishop(Pos pos);
    ~Bishop();
    };

    class Knight : private Figure{
        public:
            vector <Pos> possible_moves(Figure * Board[]);
    Knight(Pos pos);
    ~Knight();
    };

    class King : private Figure{
        public:
            vector <Pos> possible_moves(Figure * Board[]);
            bool not_in_danger( Figure * Board[], bool color);
    King(Pos pos);
    ~King();
    };

#endif //FIGURES_H
