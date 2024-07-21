//
// Created by merom on 5/24/2024.
//

#ifndef CHESS_CONTROLLER_H
#define CHESS_CONTROLLER_H
#include "PolyMatrix.h"
#include <unordered_map>
#include <Coordinate.h>
#include <sstream>
#include <algorithm>
#include "MetaData.h"
#include "Bishop.h"
#include "Blank.h"
#include "Knight.h"
#include "King.h"
#include "Pawn.h"
#include "Rook.h"
#include "Queen.h"
#include <list>
#include <algorithm>
#include <array>

using shared_Piece = std::shared_ptr<Piece> ;
using white_list = std::list<shared_Piece>;
using black_list = std::list<shared_Piece>;
using possible_move_list = std::list<Coordinate>;
using pawnMapMoves = std::unordered_map<std::string,possible_move_list>;
using map_type_id = const std::unordered_map< std::string,  std::string>;



class Controller{
public:

    Controller(const Controller&) = delete;
    Controller &operator=(const Controller&) = delete;
    static Controller& getInstance(Matrix& mat);
    static Controller& getInstance();
    METADATA isValidMove(const std::string & uncoded);

private:

   /* General function to evaluate pieces */
   METADATA evaluatePieces(const shared_Piece& p1, const shared_Piece& p2);

    /* Rook section */
    METADATA isValidMoveRook(const shared_Piece& curr, const shared_Piece& dest);
    possible_move_list getRookPossibleMoves(const shared_Piece& curr);
    /******************/

    /* King section */
    METADATA isValidMoveKing(const shared_Piece& curr, const shared_Piece& dest);
    possible_move_list getKingPossibleMoves(const shared_Piece& king);
    /*******************/

    /* Knight section */
    METADATA isValidMoveKnight(const shared_Piece& curr, const shared_Piece& dest);
    possible_move_list getKnightPossibleMoves(const shared_Piece& curr);
    /******************/

    /* Bishop section */
    METADATA isValidMoveBishop(const shared_Piece& curr, const shared_Piece& dest);
    possible_move_list getBishopPossibleMoves(const shared_Piece& bishop);
    /******************/

    /* Queen section */
    METADATA isValidMoveQueen(const shared_Piece& curr, const shared_Piece& dest);
    possible_move_list getQueenPossibleMoves(const shared_Piece& queen);
    /*******************/

    /* Pawn section */
    METADATA isValidMovePawn(shared_Piece curr, const shared_Piece& dest);
    pawnMapMoves  getPawnPossibleMoves(const shared_Piece& curr); // can be changed
    /******************/


    /*Check for a check and king section*/
    bool isKingInCheck(Color kingColor);
    Coordinate findKingPosition(Color kingColor);
    possible_move_list getAllOpponentMoves(Color kingColor);
    bool isSafeMove(const shared_Piece& piece, Coordinate newCoord);
    bool isCheckmate(Color kingColor);
    shared_Piece findKing(Color kingColor);
    bool willMoveCauseCheck(const shared_Piece& current_piece, const shared_Piece& des_piece);
    /******************************/


    /* Utilities functions */
    possible_move_list getPossibleMoves(const shared_Piece& piece);

    /* If player played, this is the supposed color*/
    Color SupposedCurrentPlayerPieceColor() const;

    /* Decode the giving string, for example, a1b1 => a1=(0,0)  b1=(1,0)*/
    Coordinate decode(const std::string & s);

    /* Get a piece at location c*/
    shared_Piece getPiece(Coordinate c);

    /* Change player turn*/
    void change_Turn(METADATA data);

    /* Check of the location within the boundaries */
    bool isValidPosition(int row, int col);

    /* If piece is white or black Piece convert it to other piece and added to the white or black list*/
    void convertPieceAndaddItToBlackWhiteList(const Coordinate &cord, const std::string &newPieceType, Color newPieceColor);

    /* Remove a current piece to the white/black list*/
    void removePieceFromList(const shared_Piece& piece);

    /* Add a current piece to the white/black list*/
    void addPieceToList(const shared_Piece& piece);


    /* Add the move to the list if it's valid*/
    bool addMoveIfValid(possible_move_list& moves, Coordinate coord, Color currColor);

    /* Change a current piece to blank and the destination(blank) to the current piece*/
    METADATA changePiceToBlankAndOpposite(shared_Piece curr, shared_Piece des);

    /* Attack the destination piece */
    METADATA attackPiece(shared_Piece curr, shared_Piece des);

    explicit Controller(Matrix & mat);


    static std::unique_ptr<Controller> instance;

    bool white_turn = true;

    /* Reference for the board pieces */
    Matrix & _mat_ref;

    /* Lists that contain only black or white pieces */
    white_list _white_list;
    black_list _black_list;

    /* will be used later to map the decoded string to it's coordinate*/
    std::unordered_map<std::string,Coordinate> _map;

    // Create the map
    map_type_id pieceSymbolToNameMap = {
            {"♝", "Bishop"},
            {"[", "Blank"},
            {"♚", "King"},
            {"♞", "Knight"},
            {"♟", "Pawn"},
            {"♛", "Queen"},
            {"♜", "Rook"}
    };


    //Create the map
    map_type_id _type_id_to_icon_map = {
            {typeid(Bishop).name(), "♝"},
            {typeid(Blank).name(), "["},
            {typeid(King).name(), "♚"},
            {typeid(Knight).name(), "♞"},
            {typeid(Pawn).name(), "♟"},
            {typeid(Queen).name(), "♛"},
            {typeid(Rook).name(), "♜"}
    };


};
#endif //CHESS_CONTROLLER_H
