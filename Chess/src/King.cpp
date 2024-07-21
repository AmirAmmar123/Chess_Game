//
// Created by merom on 5/24/2024.
//
#include "King.h"

registerInFactory<Piece, King> king_factory("King");

King::King(Coordinate cord, Color type) : Piece(cord, type) {

}

King *King::createInstance(Coordinate cord,Color type) {
    return new King(cord,type);
}

