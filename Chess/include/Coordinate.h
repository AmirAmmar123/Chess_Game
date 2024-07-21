//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_COORDINATE_H
#define CHESS_COORDINATE_H
#include <iostream>
struct Coordinate{
    int  r;
    int  c;

    bool operator==(const Coordinate &rhs) const {
        return r == rhs.r &&
               c == rhs.c;
    }


};
#endif //CHESS_COORDINATE_H
