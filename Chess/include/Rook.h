//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H
#include "Piece.h"
#include "PieceFactory.h"
class Rook : public Piece {
public:

    Rook(Coordinate cord, Color color);
    static Rook* createInstance(Coordinate cord, Color color);
    ~Rook() override = default;
};

#endif //CHESS_ROOK_H
