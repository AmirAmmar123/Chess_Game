//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_BLANK_H
#define CHESS_BLANK_H
#include "Piece.h"

class Blank : public Piece{
public:
    explicit Blank(Coordinate cord, Color color = Color::Blank);
    static Blank * createInstance(Coordinate cord,Color type);

};
#endif //CHESS_BLANK_H
