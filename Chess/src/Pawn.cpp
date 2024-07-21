//
// Created by merom on 5/24/2024.
//
#include "Pawn.h"
#include "PieceFactory.h"

registerInFactory<Piece, Pawn> pawn_factory("Pawn");

Pawn::Pawn(Coordinate cord, Color type) : Piece(cord, type) {

}

Pawn *Pawn::createInstance(Coordinate cord,Color type) {
    return new Pawn(cord,type);
}

