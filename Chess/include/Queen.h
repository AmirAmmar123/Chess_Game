//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "Piece.h"
#include "PieceFactory.h"
class Queen : public Piece {
public:

    Queen(Coordinate cord, Color color);
    static Queen* createInstance(Coordinate cord, Color color);
    ~Queen() override = default;
};
#endif //CHESS_QUEEN_H
