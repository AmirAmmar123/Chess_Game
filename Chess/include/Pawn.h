//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"
class Pawn : public Piece {
public:
    Pawn(Coordinate cord, Color color);
    static Pawn* createInstance(Coordinate cord, Color color);
    ~Pawn() override = default;

};

#endif //CHESS_PAWN_H
