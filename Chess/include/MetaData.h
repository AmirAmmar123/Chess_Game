//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_MOVINGMETADATA_H
#define CHESS_MOVINGMETADATA_H

#endif //CHESS_MOVINGMETADATA_H

enum class  METADATA{
    // illegal moves
    NoPiceInTheOriginalSquare = 11,
    InTheOriginalSquareOponentThere = 12,
    InTheDestinationSquareFriendThere = 13,
    IllegalActionMadeByPice = 21,
    TheMoveWillResultInaCheck = 31,

    // legal moves
    CheckMate = 41,
    LegalAction = 42
};

// Cannot perform the move - each code represents a different reason
// 11 - No piece in the source square.
// 12 - The source square contains a piece of the opposing player.
// 13 - The target square contains a piece of the player making the move.
// 21 - The move of the piece is not legal, for example, a rook trying to move diagonally or another piece blocking the movement.
// 31 - The move will result in a check against the player making the move (see example 3).

// The move can be performed
// 42 - Legal move. The piece will disappear from the source square on the board, be placed on the target square, and the turn will switch.
// 41 - Legal move causing a check. The piece will disappear from the source square on the board, be placed on the target square, the turn will switch, and a notification will also be displayed indicating that a check has been made.
