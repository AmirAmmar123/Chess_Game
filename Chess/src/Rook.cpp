//
// Created by merom on 5/24/2024.
//

#include "Piece.h"
#include "Rook.h"
registerInFactory<Piece, Rook> rook_factory("Rook");

Rook::Rook(Coordinate cord, Color type) : Piece(cord, type) {

}

Rook *Rook::createInstance(Coordinate cord,Color type) {
    return new Rook(cord,type);
}

