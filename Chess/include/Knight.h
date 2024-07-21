//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H
#include "Piece.h"
class Knight : public Piece {
public:

    Knight(Coordinate cord, Color color);
    static Knight* createInstance(Coordinate cord, Color color);
    ~Knight() override = default;
};
#endif //CHESS_KNIGHT_H
