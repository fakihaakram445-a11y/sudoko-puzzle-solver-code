#include <iostream>
#include <fstream>
using namespace std;

const int n = 9;
int original[n][n]; // to store original puzzle

// Function to check if a number is safe to place
bool isSafe(int board[n][n], int row, int col, int num) {
    for (int x = 0; x < n; x++) {
        if (board[row][x] == num || board[x][col] == num)
            return false;
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num)
                return false;
        }
    }
    return true;
}

// Recursive function to solve Sudoku
bool solveSudoku(int board[n][n], int row, int col) {
    if (row == n) return true;

    int nextRow = row, nextCol = col + 1;
    if (nextCol == n) {
        nextRow++;
        nextCol = 0;
    }

    if (board[row][col] != 0) {
        return solveSudoku(board, nextRow, nextCol);
    }

    for (int digit = 1; digit <= 9; digit++) {
        if (isSafe(board, row, col, digit)) {
            board[row][col] = digit;
            if (solveSudoku(board, nextRow, nextCol))
                return true;
            board[row][col] = 0; // backtrack
        }
    }
    return false;
}

// Function to print the Sudoku board
void printBoard(int board[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to print the original puzzle
void printOriginal() {
    cout << "\nOriginal Puzzle:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << original[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to save the original puzzle to a file
void savePuzzleToFile() {
    ofstream fout("sudoku_puzzle.txt");
    fout << "Original Puzzle:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fout << original[i][j] << " ";
        }
        fout << endl;
    }
    fout.close();
    cout << "\nOriginal puzzle saved to file: sudoku_puzzle.txt\n";
}

// Function to save the solved puzzle to the same file
void saveSolvedToFile(int board[n][n]) {
    ofstream fout("sudoku_puzzle.txt", ios::app); // append mode
    fout << "\nSolved Puzzle:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fout << board[i][j] << " ";
        }
        fout << endl;
    }
    fout.close();
    cout << "Solved puzzle also saved to file: sudoku_puzzle.txt\n";
}

int main() {
    int board[n][n];

    cout << "Enter Sudoku Puzzle (use 0 for empty cells):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
            original[i][j] = board[i][j]; // save original puzzle
        }
    }

    // Save original puzzle to file
    savePuzzleToFile();

    // Solve the puzzle
    if (solveSudoku(board, 0, 0)) {
        printOriginal(); // Show original
        cout << "\nSolved Puzzle:\n";
        printBoard(board);
        saveSolvedToFile(board); // Save solved puzzle
    } else {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}

