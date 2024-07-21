//
// Created by merom on 5/24/2024.
//

#include "Bishop.h"

registerInFactory<Piece, Bishop> bishop_factory("Bishop");

Bishop::Bishop(Coordinate cord, Color type) : Piece(cord, type) {

}

Bishop *Bishop::createInstance(Coordinate cord,Color type) {
    return new Bishop(cord,type);
}

