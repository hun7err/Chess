#ifndef FIGURES_H
    #define FIGURES_H

    #include "chess.h"

    class Pawn : Figure{
        public:
            vector <Pos> possibe_moves(Figure * Board[8][8]);
    Pawn(Pos pos);
    ~Pawn();
    };

    class Queen : Figure{
        public:
            vector <Pos> possibe_moves(Figure * Board[8][8]);
    Queen(Pos pos);
    ~Queen();
    };

    class Rook : Figure{
        public:
            vector <Pos> possibe_moves(Figure * Board[8][8]);
    Rook(Pos pos);
    ~Rook();
    };

    class Bishop : Figure{
        public:
            vector <Pos> possibe_moves(Figure * Board[8][8]);
    Bishop(Pos pos);
    ~Bishop();
    };

    class Knight : Figure{
        public:
            vector <Pos> possibe_moves(Figure * Board[8][8]);
    Knight(Pos pos);
    ~Knight();
    };

    class King : Figure{
        public:
            vector <Pos> possibe_moves(Figure * Board[8][8]);
            bool not_in_danger( Figure * Board[8][8], bool color);
    King(Pos pos);
    ~King();
    };

#endif //FIGURES_H
