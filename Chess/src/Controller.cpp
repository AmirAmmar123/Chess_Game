//
// Created by merom on 5/24/2024.
//
#include "Controller.h"

#include <utility>

// ctr
// Initialize the static member variable
std::unique_ptr<Controller> Controller::instance = nullptr;


Controller &Controller::getInstance(Matrix &mat) {
    if (!instance) {
        instance = std::unique_ptr<Controller>(new Controller(mat) );

    }
    return *instance;
}

Controller &Controller::getInstance() {
    return *instance;
}


Controller::Controller(Matrix &mat) :_mat_ref(mat){
    std::string letter = "abcdefgh";
    std::string numbers = "12345678";
    for (int i = 0; i < mat.getSize(); ++i) {
        for (int j = 0; j < mat.getSize(); ++j) {
            if(_mat_ref.getPiece({i,j})->get_color() == Color::WHITE ) _white_list.emplace_back(_mat_ref.getPiece({i,j}));
            if( _mat_ref.getPiece({i,j})->get_color() == Color::BLACK) _black_list.emplace_back(_mat_ref.getPiece({i,j}));
            std::stringstream ss;
            ss << letter[i];
            ss << numbers[j];
            _map[ss.str()] ={i,j};
        }
    }
}



Coordinate Controller::decode(const std::string &s) {
    return _map[s];
}

shared_Piece Controller::getPiece(Coordinate c) {
    return _mat_ref.getPiece(c);
}



METADATA Controller::isValidMove( const std::string & coded) {
    /* decode the string into coordinates and retrieve pieces */
    auto metaData = this->evaluatePieces
            (
              this->getPiece(this->decode(coded.substr(0,2))),
              this->getPiece(this->decode(coded.substr(2)))
            );

    change_Turn(metaData);

    if (metaData == METADATA::LegalAction || metaData == METADATA::CheckMate) {
        if (isCheckmate(SupposedCurrentPlayerPieceColor())) {
            return METADATA::CheckMate;
        }
    }

    return metaData;
}


METADATA Controller::evaluatePieces(const shared_Piece& current_piece, const shared_Piece& des_piece) {
    // Retrieve the type ID of the current piece
    std::string id_current = _type_id_to_icon_map.find(typeid(*current_piece).name())->second;

    // Check if there's no piece in the original square
    if (id_current == "[") return METADATA::NoPiceInTheOriginalSquare;

    // Check if the player is using the opponent's piece
    if(current_piece->get_color() != SupposedCurrentPlayerPieceColor() && current_piece->get_color() != Color::Blank) {
        return METADATA::InTheOriginalSquareOponentThere;
    }

    METADATA moveResult;
    // Evaluate the move based on the piece type


    if (willMoveCauseCheck(current_piece, des_piece)) {
            moveResult = METADATA::TheMoveWillResultInaCheck;
    }else if (id_current == "♝") {
        // Handle Bishop
        moveResult = isValidMoveBishop(current_piece, des_piece);
    } else if (id_current == "♚") {
        // Handle King
        moveResult = isValidMoveKing(current_piece, des_piece);
    } else if (id_current == "♞") {
        // Handle Knight
        moveResult = isValidMoveKnight(current_piece, des_piece);
    } else if (id_current == "♟") {
        // Handle Pawn
        moveResult = isValidMovePawn(current_piece, des_piece);
    } else if (id_current == "♛") {
        // Handle Queen
        moveResult = isValidMoveQueen(current_piece, des_piece);
    } else if (id_current == "♜") {
        // Handle Rook
        moveResult = isValidMoveRook(current_piece, des_piece);
    }



    return moveResult;
}



/* Working on it, 6/3/2024                   (Rook)
 * All moves calculated, and if des blankly or opponent handled 6/3/2024
 * Need to Handle check ... not done yet
 * */

/***************** Rook *******************************/
METADATA Controller::isValidMoveRook(const shared_Piece& curr, const shared_Piece& dest) {
    auto moves = getRookPossibleMoves(curr);

    // Get the destination position
    Coordinate destPos = dest->getLoacation();

    // Ensure the destination is not occupied by a friendly piece
    if (dest->get_color() == curr->get_color()) {
        return METADATA::InTheDestinationSquareFriendThere;
    }


    // Check if the destination is a valid move for the Rook
    if (std::find(moves.begin(), moves.end(), destPos) == moves.end()) {
        return METADATA::IllegalActionMadeByPice;
    }


    // check if the des is a blank
    if(dest->get_color() == Color::Blank ){
        return changePiceToBlankAndOpposite(curr,dest);
    }

    // if not attack des
    return attackPiece(curr,dest);


}


possible_move_list Controller::getRookPossibleMoves(const shared_Piece& curr) {
    possible_move_list moves;
    Coordinate currPos = curr->getLoacation();  // Assuming getLoacation() is correct

    // Directions the Rook can move: vertical and horizontal
    static std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (const auto& direction : directions) {
        int r = currPos.r + direction.first;
        int c = currPos.c + direction.second;

        while (isValidPosition(r, c)) {
            Coordinate newPos(r, c);
            shared_Piece pieceAtNewPos = getPiece(newPos);

            if (pieceAtNewPos->get_color() == Color::Blank) {
                moves.push_back(newPos);
            } else {
                if (pieceAtNewPos->get_color() != curr->get_color()) {
                    moves.push_back(newPos);
                }
                break;
            }
            r += direction.first;
            c += direction.second;
        }
    }

    return moves;
}
/***************** Rook *******************************/

/***************** King *******************************/
METADATA Controller::isValidMoveKing(const shared_Piece& curr, const shared_Piece& dest) {
    auto moves = getPossibleMoves(curr);

    // Get the destination position
    Coordinate destPos = dest->getLoacation();

    // Check if the destination is a valid move for the King
    if (std::find(moves.begin(), moves.end(), destPos) == moves.end()) {
        return METADATA::IllegalActionMadeByPice;
    }

    // Ensure the destination is not occupied by a friendly piece
    if (dest->get_color() == curr->get_color()) {
        return METADATA::InTheDestinationSquareFriendThere;
    }

    // Perform additional checks if necessary...

    // If all checks pass, return that it's a legal action
    return METADATA::LegalAction;
}


possible_move_list Controller::getKingPossibleMoves(const shared_Piece& king) {
    possible_move_list kingMoves;
    std::vector<std::vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (const auto& dir : directions) {
        int newRow = king->getLoacation().r + dir[0];
        int newCol = king->getLoacation().c + dir[1];

        if (isValidPosition(newRow, newCol)) {
            kingMoves.push_back({newRow, newCol});
        }
    }
    return kingMoves;
}
/***************** King *******************************/

/***************** Knight *******************************/
METADATA Controller::isValidMoveKnight(const shared_Piece& curr, const shared_Piece& dest) {
    auto knightPossibleMoves = getPossibleMoves(curr);
    auto it = std::find( knightPossibleMoves.begin(), knightPossibleMoves.end(), dest->getLoacation());


    /*if the destination is a piece that belongs to the current player */
    if( dest->get_color() == curr->get_color()){
        return METADATA::InTheDestinationSquareFriendThere;
    }

    /*if the destination is not legal*/
    if (it == knightPossibleMoves.end()){
        return METADATA::IllegalActionMadeByPice;
    }

    // check if the des is a blank
    if(dest->get_color() == Color::Blank ){
        return changePiceToBlankAndOpposite(curr,dest);
    }

    // if not then attack des
    return attackPiece(curr,dest);

}


possible_move_list Controller::getKnightPossibleMoves(const shared_Piece& curr) {
    // Define the possible x and y offsets for knight movements
    static constexpr std::array<int, 8> dx = {2, 1, -1, -2, -2, -1, 1, 2};
    static constexpr std::array<int, 8> dy = {1, 2, 2, 1, -1, -2, -2, -1};

    possible_move_list knight_moves;
    Coordinate currentPos = curr->getLoacation();

    // Calculate possible moves for the knight
    for (size_t i = 0; i < dx.size(); ++i) {
        int newX = currentPos.r + dx[i];
        int newY = currentPos.c + dy[i];

        if (isValidPosition(newX, newY)) {
            knight_moves.push_back({newX, newY});
        }
    }

    return knight_moves;
}
/***************** Knight *******************************/

/***************** Bishop *******************************/
METADATA Controller::isValidMoveBishop(const shared_Piece& curr, const shared_Piece& dest) {
    // Get possible moves for the bishop from the current position
    possible_move_list bishopMoves = getPossibleMoves(curr);

    // Check if the destination is in the list of possible moves
    auto it = std::find(bishopMoves.begin(), bishopMoves.end(), dest->getLoacation());
    if (it == bishopMoves.end()) {
        // Destination is not a valid move for the bishop
        return METADATA::IllegalActionMadeByPice;
    }

    // Check if the destination square is occupied by a friendly piece
    if (dest->get_color() == curr->get_color()) {
        return METADATA::InTheDestinationSquareFriendThere;
    }

    // check if the des is a blank
    if(dest->get_color() == Color::Blank ){
        return changePiceToBlankAndOpposite(curr,dest);
    }

    // if not then attack des
    return attackPiece(curr,dest);

}



possible_move_list Controller::getBishopPossibleMoves(const shared_Piece& bishop) {
    possible_move_list bishopMoves;

    auto r = bishop->getLoacation().r;
    auto c = bishop->getLoacation().c;

    auto curr_color = bishop->get_color();

    for (int i = 1; isValidPosition(r + i, c + i); ++i) {
        if (!addMoveIfValid(bishopMoves, {r + i, c + i}, curr_color)) break;
    }
    for (int i = 1; isValidPosition(r + i, c - i); ++i) {
        if (!addMoveIfValid(bishopMoves, {r + i, c - i}, curr_color)) break;
    }
    for (int i = 1; isValidPosition(r - i, c + i); ++i) {
        if (!addMoveIfValid(bishopMoves, {r - i, c + i}, curr_color)) break;
    }
    for (int i = 1; isValidPosition(r - i, c - i); ++i) {
        if (!addMoveIfValid(bishopMoves, {r - i, c - i}, curr_color)) break;
    }

    return bishopMoves;
}
/***************** Bishop *******************************/

/***************** Pawn *******************************/
pawnMapMoves  Controller::getPawnPossibleMoves(const shared_Piece& curr) {
    pawnMapMoves mapMoves;
    // Define movement direction based on pawn color
    int direction = (curr->get_color() == Color::WHITE) ? 1 : -1; // White pawns move up (+1), black pawns move down (-1)

    // Single square move
    int newRow = curr->getLoacation().r + direction;
    if (isValidPosition(newRow, curr->getLoacation().c)) {
        mapMoves["peaceful"].push_back({newRow, curr->getLoacation().c});
    }

    // Double square move from starting position
    if ((curr->get_color() == Color::WHITE && curr->getLoacation().r == 1) ||
        (curr->get_color() == Color::BLACK && curr->getLoacation().r == 6)) {
        int doubleMoveRow = newRow + direction;
        if (isValidPosition(doubleMoveRow, curr->getLoacation().c)) {
            mapMoves["peaceful"].push_back({doubleMoveRow, curr->getLoacation().c});
        }
    }

    // Capture moves (diagonal moves)
    int newCols[] = {curr->getLoacation().c - 1, curr->getLoacation().c + 1};
    for (int newCol : newCols) {
        if (isValidPosition(newRow, newCol)) {
            mapMoves["capture"].push_back({newRow, newCol});
        }
    }

    /* add the possibility to transform*/
    return mapMoves;
}


METADATA Controller::isValidMovePawn(shared_Piece curr, const shared_Piece& dest) {
    /* return peaceful moves and capture moves*/
    auto pawnMoves = getPawnPossibleMoves(curr);

    auto peace_iter = std::find(pawnMoves["peaceful"].begin(), pawnMoves["peaceful"].end(), dest->getLoacation());
    auto capture_iter = std::find(pawnMoves["capture"].begin(), pawnMoves["capture"].end(),dest->getLoacation());

    /* Illegal move indication, if both iterators are at end of list*/
    if(peace_iter == pawnMoves["peaceful"].end() && capture_iter == pawnMoves["capture"].end()){
        return METADATA::IllegalActionMadeByPice;
    }

    // check if the des is a blank
    if(dest->get_color() == Color::Blank ){
        return changePiceToBlankAndOpposite(std::move(curr),dest);
    }

    auto it = std::find(pawnMoves["capture"].begin(), pawnMoves["capture"].end(), dest->getLoacation());

    if (it != pawnMoves["capture"].end()) {
        return attackPiece(curr,dest);
    }

    return METADATA::IllegalActionMadeByPice;
}
/***************** Pawn *******************************/

/***************** Queen *******************************/
METADATA Controller::isValidMoveQueen(const shared_Piece& curr, const shared_Piece& dest) {
    auto moves = getPossibleMoves(curr);
    return METADATA::CheckMate;
}

possible_move_list Controller::getQueenPossibleMoves(const shared_Piece& queen) {
    possible_move_list queenMoves;
    auto rookMoves = getRookPossibleMoves(queen);
    auto bishopMoves = getBishopPossibleMoves(queen);

    queenMoves.insert(queenMoves.end(), rookMoves.begin(), rookMoves.end());
    queenMoves.insert(queenMoves.end(), bishopMoves.begin(), bishopMoves.end());

    return queenMoves;
}
/***************** Queen *******************************/


void Controller::change_Turn(METADATA data) {
    if(data == METADATA::LegalAction || data == METADATA::CheckMate) white_turn = !white_turn;
}



void Controller::convertPieceAndaddItToBlackWhiteList(const Coordinate &cord, const std::string &newPieceType, Color newPieceColor) {
    // Create the new piece using the abstract factory
    auto newPiece = genericFactory<Piece>::instance().create(newPieceType, {cord.r, cord.c}, newPieceColor);
    // Add the new piece if it has a color to its own list
     addPieceToList(newPiece);
    // Replace the old piece with the new one in the matrix
    _mat_ref.setPiece(cord,newPiece);
}

Color Controller::SupposedCurrentPlayerPieceColor() const {
    return (white_turn)?Color::WHITE :Color::BLACK;
}




// Function to check if a position is within the chessboard bounds
bool Controller::isValidPosition(int row, int col) {
    int size = this->_mat_ref.getSize();
    return row >= 0 && row < size && col >= 0 && col < size;
}

void Controller::removePieceFromList(const shared_Piece& piece) {
    if (piece->get_color() == Color::WHITE) {
        auto it = std::find(_white_list.begin(), _white_list.end(), piece);
        if (it != _white_list.end()) {
            _white_list.erase(it);
        }
    } else if (piece->get_color() == Color::BLACK) {
        auto it = std::find(_black_list.begin(), _black_list.end(), piece);
        if (it != _black_list.end()) {
            _black_list.erase(it);
        }
    }
}

void Controller::addPieceToList(const shared_Piece& piece) {
    if(piece->get_color()  == Color::WHITE){
        _white_list.emplace_back(piece);
    }else if(piece->get_color() == Color::BLACK ){
        _black_list.emplace_back(piece);
    }
}



/* Find if the king is in check */
bool Controller::isKingInCheck(Color kingColor){
    auto opponentMoves = getAllOpponentMoves(kingColor);
    return std::find(opponentMoves.begin(), opponentMoves.end(), findKingPosition(kingColor) ) != opponentMoves.end();
}



/* Find the king position */
Coordinate Controller::findKingPosition(Color kingColor) {
    for (const auto& piece : (kingColor == Color::WHITE ? _white_list : _black_list)) {
        if (_type_id_to_icon_map.find(typeid(*piece).name())->second == "♚") {
            return piece->getLoacation();
        }
    }
    throw std::runtime_error("King not found on the board");
}


/* Get all opponent pieces*/
possible_move_list Controller::getAllOpponentMoves(Color kingColor) {
    possible_move_list opponentMoves;

    for (const auto& piece : (kingColor == Color::WHITE ? _black_list : _white_list) ) {
        if(typeid(*piece).name() == typeid(Pawn).name()){
            auto pieceMoves = getPawnPossibleMoves(piece)["Capture"];
            opponentMoves.insert(opponentMoves.end(), pieceMoves.begin(), pieceMoves.end());
        }else{
            auto pieceMoves = getPossibleMoves(piece);
            opponentMoves.insert(opponentMoves.end(), pieceMoves.begin(), pieceMoves.end());
        }

    }
    return opponentMoves;
}




bool Controller::isSafeMove(const shared_Piece& piece, Coordinate newCoord) {
    auto originalCoord = piece->getLoacation();
    auto originalPiece = _mat_ref.getPiece(newCoord);

    _mat_ref.setPiece(newCoord, piece);
    _mat_ref.setPiece(originalCoord, std::make_shared<Blank>(originalCoord, Color::Blank));

    bool isSafe = !isKingInCheck(piece->get_color());

    _mat_ref.setPiece(originalCoord, piece);
    _mat_ref.setPiece(newCoord, originalPiece);

    return isSafe;
}


possible_move_list Controller::getPossibleMoves(const shared_Piece& piece) {
    std::string pieceType = _type_id_to_icon_map.find(typeid(*piece).name())->second ;
    if (pieceType == "♚") {
        return getKingPossibleMoves(piece);
    } else if (pieceType == "♛") {
       return  getQueenPossibleMoves(piece);
    } else if (pieceType == "♜") {
         return getRookPossibleMoves(piece);
    } else if (pieceType == "♝") {
        return getBishopPossibleMoves(piece);
    } else if (pieceType == "♞") {
        return getKnightPossibleMoves(piece);
    }
    return {};
}

bool Controller::isCheckmate(Color kingColor) {
    auto king_cord = findKingPosition(kingColor);
    auto kingMoves = getKingPossibleMoves(getPiece(king_cord));

    for (const auto& move : kingMoves) {
        if (isSafeMove(getPiece(king_cord), move)) {
            return false; // The king can move to a safe position
        }
    }

    // Check if any other piece can block or capture the threatening piece
    const auto& pieceList = (kingColor == Color::WHITE ? _white_list : _black_list);
    for (const auto& piece : pieceList) {
        if (piece == getPiece(king_cord)) continue;
        auto possibleMoves = getPossibleMoves(piece);
        for (const auto& move : possibleMoves) {
            auto originalCoord = piece->getLoacation();
            auto originalPiece = _mat_ref.getPiece(move);

            _mat_ref.setPiece(move, piece);
            _mat_ref.setPiece(originalCoord, std::make_shared<Blank>(originalCoord, Color::Blank));

            bool canBlockOrCapture = !isKingInCheck(kingColor);

            _mat_ref.setPiece(originalCoord, piece);
            _mat_ref.setPiece(move, originalPiece);

            if (canBlockOrCapture) {
                return false; // A piece can block or capture the threatening piece
            }
        }
    }

    return true; // No legal moves can prevent checkmate
}

shared_Piece Controller::findKing(Color kingColor) {
    for (const auto &piece: (kingColor == Color::WHITE ? _white_list : _black_list)) {
        if (_type_id_to_icon_map.find(typeid(*piece).name())->second == "♚") {
            return piece;
        }
    }
    throw std::runtime_error("King not found on the board");
}


bool Controller::addMoveIfValid(possible_move_list& moves, Coordinate coord, Color currColor) {
    auto targetPiece = getPiece(coord);
    if (targetPiece->get_color() == currColor) {
        return false;
    }
    moves.push_back(coord);
    return targetPiece->get_color() == Color::Blank;
}

METADATA Controller::changePiceToBlankAndOpposite(shared_Piece curr, shared_Piece dest) {
    // remove the current piece of the white/black list

    removePieceFromList(curr);
    this->convertPieceAndaddItToBlackWhiteList(dest->getLoacation(),
                                               pieceSymbolToNameMap.find(
                                                       _type_id_to_icon_map.find(
                                                               typeid(*curr).name()
                                                               )->second
                                               )->second,
                                               curr->get_color());
    this->convertPieceAndaddItToBlackWhiteList(curr->getLoacation(), "Blank", Color::Blank);

    curr.reset(); // new obj created, kill the previous, release it from memory
    dest.reset(); // new obj created, kill the previous, release it from memory
    return METADATA::LegalAction;

}

METADATA Controller::attackPiece(shared_Piece curr, shared_Piece dest) {
    // remove the current piece of the white/black list

    removePieceFromList(curr);
    removePieceFromList(dest);

    this->convertPieceAndaddItToBlackWhiteList
    (
            dest->getLoacation(),
            pieceSymbolToNameMap.find(
                    _type_id_to_icon_map.find(
                            typeid(*curr).name()
                            )->second
            )->second,
            curr->get_color()
    );

    this->convertPieceAndaddItToBlackWhiteList(curr->getLoacation(), "Blank", Color::Blank);

    curr.reset(); // new obj created, release it from memory
    dest.reset(); // new obj created, release it from memory
    return METADATA::LegalAction;
}
/**************************************/


bool Controller::willMoveCauseCheck(const shared_Piece& current_piece, const shared_Piece& des_piece) {
    // Save original positions and pieces
    auto originalCoord = current_piece->getLoacation();
    auto destinationCoord = des_piece->getLoacation();
    auto originalDestPiece = _mat_ref.getPiece(destinationCoord);

    // Remove pieces from their respective lists
    removePieceFromList(current_piece);
    if (originalDestPiece && originalDestPiece->get_color() != Color::Blank) {
        removePieceFromList(originalDestPiece);
    }

    // Make the move temporarily
    _mat_ref.setPiece(destinationCoord, current_piece);
    _mat_ref.setPiece(originalCoord, std::make_shared<Blank>(originalCoord, Color::Blank));

    // Add the current piece to its new location in the list
    addPieceToList(current_piece);

    bool causesCheck = isKingInCheck(SupposedCurrentPlayerPieceColor());

    // Undo the move
    _mat_ref.setPiece(originalCoord, current_piece);
    _mat_ref.setPiece(destinationCoord, originalDestPiece);

    // Update the piece lists back to their original state
    removePieceFromList(current_piece);  // Remove current piece from its new temporary location
    addPieceToList(current_piece);       // Add current piece back to its original location
    if (originalDestPiece && originalDestPiece->get_color() != Color::Blank) {
        addPieceToList(originalDestPiece);  // Add the original destination piece back to its original location
    }

    return causesCheck;
}

