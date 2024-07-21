//
// Created by merom on 5/24/2024.
//

#include "Knight.h"
#include "PieceFactory.h"

registerInFactory<Piece, Knight> knight_factory("Knight");

Knight::Knight(Coordinate cord, Color type) : Piece(cord, type) {

}

Knight *Knight::createInstance(Coordinate cord,Color type) {
    return new Knight(cord,type);
}


