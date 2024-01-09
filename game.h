#include <iostream>
#include <string>
#include <vector>

#define ROWS            6
#define COLUMNS         7
#define PLAYER1_COLOR   LIGHT_GREEN
#define PLAYER2_COLOR   LIGHT_MAGENTA

using namespace std;

enum Cell {
    EMPTY = 0,
    PLAYER1 = 1,
    PLAYER2 = 2
};
enum Colors {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    LIGHT_GRAY = 7,
    DARK_GRAY = 8,
    LIGHT_RED = 9,
    LIGHT_GREEN = 10,
    LIGHT_YELLOW = 11,
    LIGHT_BLUE = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_CYAN = 14,
    WHITE = 15
};

void setColor(int foreground, int background);
void setBackground(int color);
void setText(int color);
void resetColor();
int combine_ints(int a, int b);




class Group {
public:
    array<int, 4> members;
    int groupID;
    void addMember(int memberID, int position) {
        members[position] = memberID;
    }
};

struct Board {
    int rows = ROWS;
    int cols = COLUMNS;
    vector<vector<Cell>> grid;

    Board() : grid(rows, vector<Cell>(cols, EMPTY)) {}

    void display() {

        cout << endl;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                char cell = '.';
                setBackground(BLACK);

                switch (grid[r][c]) {
                    case PLAYER1:
                        cell = 'X';
                        setText(PLAYER1_COLOR);
                        break;
                    case PLAYER2:
                        cell = 'O';
                        setText(PLAYER2_COLOR);
                        break;
                    case EMPTY: cell = ' '; break;
                }
                cout << " " << cell << " ";
                resetColor();
            }
            resetColor();
            cout << endl;
        }
        setBackground(BLACK);
        setText(DARK_GRAY);
        for(int i = 0; i < cols; i++){
            cout << " " << i + 1 << " ";
        }
        resetColor();
        cout << endl;

    }
};

class Game {
private:
    Board* board;
    vector<Group> groups;
    unordered_map<int, vector<int>> personToGroups;

public:
    void displayBoard(){
        board->display();
    }

    void addGroup(Group* group, int a, int b) {
        int groupId = combine_ints(a, b);
        group->groupID = groupId;
        groups.push_back(*group);
        // Update person to group mapping
        for (int member : group->members) {
            personToGroups[member].push_back(groupId);
        }
    }

    void addBoard(Board* _board){
        board = _board;
    }

    vector<int> getGroupsForPerson(int personID) {
        if (personToGroups.find(personID) == personToGroups.end()) {
            return vector<int>();
        }
        return personToGroups[personID];
    }

    bool checkGroup(int groupID){
        int prefix = groupID / 100;
        int row = (groupID % 100) / 10 - 1;
        int col = groupID % 10 - 1;
        switch (prefix) {
            case 1:
                for(int i = 0; i < 4; i++){
                    if(board->grid[row][col] != board->grid[row + i][col])
                        return false;
                    if(board->grid[row + i][col] == EMPTY)
                        return false;
                }
                break;
            case 2:
                for(int i = 0; i < 4; i++){
                    if(board->grid[row][col] != board->grid[row][col + i])
                        return false;
                    if(board->grid[row][col + i] == EMPTY)
                        return false;
                }
                break;
            case 3:
                for(int i = 0; i < 4; i++){
                    if(board->grid[row][col] != board->grid[row + i][col + i])
                        return false;
                    if(board->grid[row + i][col + i] == EMPTY)
                        return false;
                }
                break;
            case 4:
                for(int i = 0; i < 4; i++){
                    if(board->grid[row][col] != board->grid[row + i][col - i])
                        return false;
                    if(board->grid[row + i][col - i] == EMPTY)
                        return false;
                }
                break;
            default:
                cout << "COS JEST NIE TAK" << endl;
                return false;
        }
        return true;
    }

    bool isWinning(int cellID){
        vector<int> groupIDs = getGroupsForPerson(cellID);
        for (int groupID: groupIDs) {
            if(checkGroup(groupID))
                return true;
        }
        return false;
    }

    bool verifyMove(int move){
        if(move < 1 || move > 7)
            return false;
        if(board->grid[0][move-1] != EMPTY)
            return false;
        return true;
    }

    int makeMove(int column, Cell player){
        int col = column - 1;
        for(int i = ROWS - 1; i >= 0; i--){
            if(board->grid[i][col] == EMPTY){
                board->grid[i][col] = player;
                return i + 1;
            }
        }
        return -1;
    }
};


void createGroups(Game* game);
Board* createBoard();
