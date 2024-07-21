// Chess
#include "Chess.h"
#include "PolyMatrix.h"
#include "Controller.h"
// * stands for white king
// @ stands for black king
int main()
{

    string board = "RNBQ*BNRPPPPPPPP################################pppppppprnbq@bnr";
    Matrix game (board,8);
    Controller::getInstance(game);
    Chess a(board);
    string res = a.getInput();
    while (res != "exit")
    {
        a.setCodeResponse( static_cast<int>( Controller::getInstance().isValidMove(res) ) );
        res = a.getInput();
    }

    cout << endl << "Exiting " << endl;
    return 0;
}