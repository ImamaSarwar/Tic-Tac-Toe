#include <iostream>
#include <string>
using namespace std;

char board[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };
int row = 0, column = 0, play = 1;
bool tie = false;
char sign = 'X';  // Player 1: X, Player 2: O

void Board() {
    cout << "      |        |  \n";
    cout << "   " << board[0][0] << "  |   " << board[0][1] << "    |   " << board[0][2] << endl;
    cout << "______|________|______" << endl;
    cout << "      |        |\n";
    cout << "   " << board[1][0] << "  |   " << board[1][1] << "    |   " << board[1][2] << endl;
    cout << "______|________|______" << endl;
    cout << "      |        | \n";
    cout << "   " << board[2][0] << "  |   " << board[2][1] << "    |   " << board[2][2] << endl;
    cout << "      |        |  \n";
}

bool isPositionAvailable(int pos) 
{
    char c = '0' + pos;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == c)
            {
                return true;
            }
        }
    }
    return false;
}

void GamePlay(string player1, string player2) {
    int position_choice;

    while (true) {
        if (sign == 'X')
        {
            cout << player1 << " (X), enter your move (1-9): ";
        }
        else
        {
            cout << player2 << " (O), enter your move (1-9): ";
        }

        cin >> position_choice;

        if (cin.fail() || position_choice < 1 || position_choice > 9) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << "Invalid input! Please enter a number between 1 and 9.\n";
            continue;
        }

        // Check if position is already taken
        row = (position_choice - 1) / 3;
        column = (position_choice - 1) % 3;

        if (board[row][column] != 'X' && board[row][column] != 'O') {
            board[row][column] = sign;
            sign = (sign == 'X') ? 'O' : 'X'; // switch turns
            play++;
            break;
        }
        else {
            cout << "Position already taken! Choose another.\n";
        }
    }
}

bool winner_player() {
    // Rows and columns
    for (int i = 0; i < 3; i++) 
    {
        if ((board[i][0] == board[i][1] && board[i][0] == board[i][2]) || (board[0][i] == board[1][i] && board[0][i] == board[2][i]))
        {
            return true;
        }
    }

    // Diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[0][2] == board[1][1] && board[1][1] == board[2][0]))
    {
        return true;
    }

    // Check for tie
    bool boardFull = true;
    for (int i = 0; i < 3 && boardFull; i++)
    {
        for (int j = 0; j < 3 && boardFull; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                boardFull = false;
            }
        }
    }

    if (boardFull) 
    {
        tie = true;
        return true;
    }

    return false;
}

int main() {
    string player1, player2;
    cout << "Enter name of Player 1: ";
    getline(cin, player1);
    cout << "Enter name of Player 2: ";
    getline(cin, player2);

    while (!winner_player()) {
        Board();
        GamePlay(player1, player2);
    }

    Board();

    if (tie) {
        cout << "It's a draw!\n";
    }
    else if ((play - 1) % 2 == 0) {
        cout << player2 << " wins!\n";
    }
    else {
        cout << player1 << " wins!\n";
    }

    return 0;
}
