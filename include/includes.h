#ifndef includes_h
    #define includes_h

    #include <ctime>
    #include <cstdio>
    #include <iostream>
    #include <string>
    #include <algorithm>
    #include <utility>
    #include <fstream>
    #include <vector>
    #include <list>
    #include <stack>
    #include <queue>
    #define vector std::vector
    #define list std::list
    #define stack std::stack
    #define pair std::pair
    #define string std::string

    /// Figures types (no)
    #define KING 0
    #define PAWN 1
    #define ROOK 2
    #define BISHOP 3
    #define KNIGHT 4
    #define QUEEN 5

    /// Figure::move(...) posiible returns:
    /*#define FALSE 0 // move impossible
    #define TRUE 1  // moved*/
    #define MAT 2   // end of game by winning
    #define PAT 3   // end of game by no more possible moves

    #define ABS(x) ((x) < 0) ? -(x) : x

#endif // includes_h
