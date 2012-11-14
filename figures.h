#ifndef FIGURES_H
    #define FIGURES_H

    #include "chess.h"

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
