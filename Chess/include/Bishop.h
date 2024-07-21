//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include <string>
#include "Piece.h"
#include "PieceFactory.h"
class Bishop : public Piece{
public:
    Bishop(Coordinate cord,Color color);
    static Bishop * createInstance(Coordinate cord,Color color);
    ~Bishop() override = default;
};
#endif //CHESS_BISHOP_H
