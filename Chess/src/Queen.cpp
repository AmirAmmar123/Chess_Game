//
// Created by merom on 5/24/2024.
//
#include "Queen.h"
registerInFactory<Piece, Queen> queen_factory("Queen");

Queen::Queen(Coordinate cord, Color type) : Piece(cord, type) {

}

Queen *Queen::createInstance(Coordinate cord,Color type) {
    return new Queen(cord,type);
}

