#include "game.h"


void setColor(int foreground, int background) {
    cout << "\033[38;5;" << foreground << "m"
         << "\033[48;5;" << background << "m";
}
void setBackground(int color) {
    cout << "\033[48;5;" << color << "m";
}
void setText(int color) {
    cout << "\033[38;5;" << color << "m";
}
void resetColor() {
    cout << "\033[0m";
}
int combine_ints(int a, int b) {
    return stoi(to_string(a) + to_string(b));
}

void createGroups(Game* game){
    // vertical
    for(int i = 1; i <= ROWS - 3; i++){
        for(int j = 1; j <= COLUMNS; j++){
            Group* group = new Group;
            for(int k = 0; k < 4; k++){
                group->addMember(combine_ints(i + k, j), k);
            }
            game->addGroup(group, 1, combine_ints(i, j));
            free(group);
        }
    }
    // horizontal
    for(int i = 1; i <= ROWS; i++){
        for(int j = 1; j <= COLUMNS - 3; j++){
            Group* group = new Group;
            for(int k = 0; k < 4; k++){
                group->addMember(combine_ints(i, j + k), k);
            }
            game->addGroup(group, 2, combine_ints(i, j));
            free(group);
        }
    }
    // right slash
    for(int i = 1; i <= ROWS - 3; i++){
        for(int j = 1; j <= COLUMNS - 3; j++){
            Group* group = new Group;
            for(int k = 0; k < 4; k++){
                group->addMember(combine_ints(i + k, j + k), k);
            }
            game->addGroup(group, 3, combine_ints(i, j));
            free(group);
        }
    }
    // left slash
    for(int i = 1; i <= ROWS - 3; i++){
        for(int j = 4; j <= COLUMNS; j++){
            Group* group = new Group;
            for(int k = 0; k < 4; k++){
                group->addMember(combine_ints(i + k, j - k), k);
            }
            game->addGroup(group, 4, combine_ints(i, j));
            free(group);
        }
    }
}

Board* createBoard(){
    Board* board = new Board();
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            board->grid[i][j] = EMPTY;
        }
    }
    return board;
}

