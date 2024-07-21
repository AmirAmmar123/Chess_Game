//
// Created by merom on 5/24/2024.
//
#include "Blank.h"
#include "PieceFactory.h"

registerInFactory<Piece, Blank> blank_Factory("Blank");


Blank *Blank::createInstance(Coordinate cord,Color type) {
    return new Blank(cord,type);
}

Blank::Blank(Coordinate cord, Color color) : Piece(cord, color) {

}

