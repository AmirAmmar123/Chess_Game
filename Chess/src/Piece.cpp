//
// Created by merom on 5/24/2024.
//
#include "Piece.h"

int Piece::_c = 0;
Piece::Piece(Coordinate cord, Color type) : i(_c++), _loc(cord), _color(type){ }

Piece::~Piece() { }


