#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[3][3];
char current_marker;
int current_player;

void initializeBoard() {
    char count = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = count++;
        }
    }
}

void drawBoard() {
    cout << "Tic-Tac-Toe Board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = current_marker;
        return true;
    } else {
        return false;
    }
}

int checkWinner() {
    // Rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return current_player;
        }
    }

    // Columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return current_player;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return current_player;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return current_player;
    }

    return 0; // No winner yet
}

void swapPlayerAndMarker() {
    if (current_marker == 'X') {
        current_marker = 'O';
    } else {
        current_marker = 'X';
    }

    if (current_player == 1) {
        current_player = 2;
    } else {
        current_player = 1;
    }
}

int getComputerMove() {
    int slot;
    srand(time(0)); // Initialize random seed
    while (true) {
        slot = (rand() % 9) + 1; // Random number between 1 and 9
        if (placeMarker(slot)) {
            cout << "Computer chose slot " << slot << endl;
            return slot;
        }
    }
}

void playGame() {
    int winner = 0;
    int slot;

    for (int i = 0; i < 9; i++) {
        if (current_player == 1) {
            cout << "Player " << current_player << ", enter your slot (1-9): ";
            cin >> slot;

            if (slot < 1 || slot > 9) {
                cout << "Invalid slot! Try again.\n";
                i--;
                continue;
            }

            if (!placeMarker(slot)) {
                cout << "Slot already taken! Try again.\n";
                i--;
                continue;
            }
        } else {
            slot = getComputerMove();
        }

        drawBoard();
        winner = checkWinner();

        if (winner != 0) {
            if (winner == 1) {
                cout << "Player wins!\n";
            } else {
                cout << "Computer wins!\n";
            }
            break;
        }

        swapPlayerAndMarker();
    }

    if (winner == 0) {
        cout << "It's a tie!\n";
    }
}

int main() {
    char playAgain;

    do {
        initializeBoard();
        cout << "Welcome to Tic-Tac-Toe!\n";
        cout << "You are Player 1 and your marker is 'X'. Computer is Player 2 and its marker is 'O'.\n";

        current_player = 1;
        current_marker = 'X';

        drawBoard();
        playGame();

        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "Thanks for playing!\n";

    return 0;
}
