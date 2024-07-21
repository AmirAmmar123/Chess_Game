#include "PolyMatrix.h"

#include <utility>


Matrix::Matrix(const std::string &board, int SIZE):SIZE(SIZE){
    // Elements are default-initialized by the std::vector
    _mat.reserve(SIZE* SIZE) ;
    this->Build(board);
}


std::shared_ptr<Piece> Matrix::operator()(int  row, int  col) {
    if (row >= this->SIZE || col >= this->SIZE || row < 0 || col < 0 || _mat.empty()) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return _mat[row][col];
}




std::shared_ptr<Piece> Matrix::operator()(int  row, int  col) const{
    if (row >= this->SIZE || col >= this->SIZE || row < 0 || col < 0 || _mat.empty()) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return _mat[row][col];
}



void Matrix::Build(const std::string & board){
    int k = 0;
    for (int i = 0; i < this->SIZE; ++i) {
        _mat.emplace_back();
        for (int j = 0; j < this->SIZE; ++j) {
            _mat[i].emplace_back(this->CreateItem(board[k++], i, j));
        }
    }
}


std::shared_ptr<Piece> Matrix::CreateItem(char c, int   i, int  j) {

    if ((c == 'R') || (c == 'r'))
        return (c == 'R') ? genericFactory<Piece>::instance().create("Rook", {i, j}, Color::WHITE)
                          : genericFactory<Piece>::instance().create("Rook", {i, j}, Color::BLACK);
    if ((c == 'N') || (c == 'n'))
        return (c == 'N') ? genericFactory<Piece>::instance().create("Knight", {i, j}, Color::WHITE)
                          : genericFactory<Piece>::instance().create("Knight", {i, j}, Color::BLACK);
    if ((c == 'B') || (c == 'b'))
        return (c == 'B') ? genericFactory<Piece>::instance().create("Bishop", {i, j}, Color::WHITE)
                          : genericFactory<Piece>::instance().create("Bishop", {i, j}, Color::BLACK);
    if ((c == 'Q') || (c == 'q'))
        return (c == 'Q') ? genericFactory<Piece>::instance().create("Queen", {i, j}, Color::WHITE)
                          : genericFactory<Piece>::instance().create("Queen", {i, j}, Color::BLACK);
    if ((c == 'K') || (c == 'k') || (c == '*') || (c == '@'))
        return ( (c == 'K') || (c == '*') ) ? genericFactory<Piece>::instance().create("King", {i, j}, Color::WHITE)
                          : genericFactory<Piece>::instance().create("King", {i, j}, Color::BLACK);
    if ((c == 'P') || (c == 'p'))
        return (c == 'P') ? genericFactory<Piece>::instance().create("Pawn", {i, j}, Color::WHITE)
                          : genericFactory<Piece>::instance().create("Pawn", {i, j}, Color::BLACK);
    if (c == '#')
        return genericFactory<Piece>::instance().create("Blank", {i, j}, Color::Blank);

    return nullptr;
}

std::shared_ptr<Piece> Matrix::getPiece(const Coordinate &cord) {
    return this->operator()(cord.r, cord.c);
}

void Matrix::setPiece(Coordinate orginalCoord, std::shared_ptr<Piece> piece) {
    _mat[orginalCoord.r][orginalCoord.c] = std::move(piece);
}
