#include "includes.h"

#ifndef DEFS_H
    #define DEFS_H

    /*typedef struct Position {
        short int x;
        short int y;
    } Pos;*/
class Pos {
    private:
        int x_val;
        int y_val;
    public:
        int x() const;
        int y() const;
        void setX(int _x);
        void setY(int _y);
        void set(int _x, int _y);
        void set(const Pos& position);
    Pos();
    Pos(int _x, int _y);
    Pos(const Pos& position);
    ~Pos();
};

//Pos NPos( short int x, short int y);

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

            virtual vector <Pos> possible_moves(Figure * Board[]);
            bool checkMove(Pos newPos);
            virtual void setPos(int x, int y);
            bool checkBoundaries(const Pos& newPos);
            int move(Pos newPos);
            bool changeType(int newType);
            int getVal();
        Figure();
        ~Figure();
    };

#endif // FIG_H

#ifndef FIGURES_H
    #define FIGURES_H

    class Pawn : public Figure{
        public:
            //Pos curPos;
            //void setPos(int x, int y);
            vector <Pos> possible_moves(Figure * Board[]);
    Pawn();
    ~Pawn();
    };

    class Queen : public Figure{
        public:
            //void setPos(int x, int y);
            vector <Pos> possible_moves(Figure * Board[]);
    Queen();
    ~Queen();
    };

    class Rook : public Figure{
        public:
            //void setPos(int x, int y);
            vector <Pos> possible_moves(Figure * Board[]);
    Rook();
    ~Rook();
    };

    class Bishop : public Figure{
        public:
            //void setPos(int x, int y);
            vector <Pos> possible_moves(Figure * Board[]);
    Bishop();
    ~Bishop();
    };

    class Knight : public Figure{
        public:
            //void setPos(int x, int y);
            vector <Pos> possible_moves(Figure * Board[]);
    Knight();
    ~Knight();
    };

    class King : public Figure{
        public:
            //void setPos(int x, int y);
            vector <Pos> possible_moves(Figure * Board[]);
            bool not_in_danger( Figure * Board[], bool color);
    King();
    ~King();
    };

#endif //FIGURES_H
