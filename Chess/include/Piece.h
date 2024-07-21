//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "Coordinate.h"
#include "Color.h"
#include <List>

class Piece{
    static int _c;
protected:
    int i;
    Piece(Coordinate cord, Color type);
public:

    virtual ~Piece();
    Coordinate getLoacation() const {
        return _loc;
    }
    Color get_color() const{
        return _color;
    }

    void setNewLocation(Coordinate newLocation){
        _loc = newLocation;
    }

private:
    Coordinate _loc;
    Color _color;
};

#endif //CHESS_PIECE_H
