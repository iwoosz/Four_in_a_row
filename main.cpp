#include "game.h"


int main() {
    Cell player = PLAYER1;
    string column;


    Game game;
    game.addBoard(createBoard());
    createGroups(&game);
    while(true){
        cout << endl;
        cout << endl;
        game.displayBoard();
        cout << "Enter column 1-7: ";
        cin >> column;
        int col = stoi(column);

        if(!game.verifyMove(col)) {
            cout << "WRONG MOVE" << endl;
            continue;
        }

        int row = game.makeMove(col, player);
        if(game.isWinning(stoi(to_string(row) + column))){
            int colorToBeSet = player == PLAYER1 ? PLAYER1_COLOR : PLAYER2_COLOR;
            game.displayBoard();
            setColor(BLACK, colorToBeSet);
            cout << endl;
            cout << endl;
            cout << "               Player " << player << " has won!" << endl;
            cout << endl;
            cout << endl;
            resetColor();

            break;
        }
        player = player == PLAYER1 ? PLAYER2 : PLAYER1;
    }
    return 0;
}