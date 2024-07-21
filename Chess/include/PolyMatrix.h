#ifndef CHESS_POLYMATRIX_H
#define CHESS_POLYMATRIX_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "PieceFactory.h"
#include "Piece.h"



class Matrix {
public:
    // Constructor
    Matrix(const std::string& board, int size);

    // Access element (non-const version)
    std::shared_ptr<Piece> operator()(int row, int  col);

    // Access element (const version)
    std::shared_ptr<Piece> operator()(int  row, int  col) const;

    std::shared_ptr<Piece> getPiece(const Coordinate & cord);

    std::vector<std::vector<std::shared_ptr<Piece>>> & getGameMatrix(){
        return _mat;
    }

    void setPiece(Coordinate orginalCoord,  std::shared_ptr<Piece>  piece);

    int getSize() const{
        return SIZE;
    }
private:
    // Helper function to get the correct piece
    std::shared_ptr<Piece> CreateItem(char c, int  i, int  j);

    // Build the matrix
    void Build(const std::string& board);

    // Matrix to hold the shared pointers
    int const SIZE;

    std::vector<std::vector<std::shared_ptr<Piece>>> _mat;
};



#endif // CHESS_POLYMATRIX_H
