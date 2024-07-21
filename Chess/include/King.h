//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H
#include "Piece.h"
#include "PieceFactory.h"
class King : public Piece {
public:

    King(Coordinate cord, Color color);
    static King* createInstance(Coordinate cord, Color color);
    ~King() override = default;
};
#endif //CHESS_KING_H
