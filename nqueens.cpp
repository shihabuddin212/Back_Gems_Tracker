#include <iostream>
#include <vector>
using namespace std;

class NQueens {
private:
    int n;
    vector<vector<int>> board;
    
    // Check if placing queen at (row, col) is safe
    bool isSafe(int row, int col) {
        // Check column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 1) {
                return false;
            }
        }
        
        // Check upper left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 1) {
                return false;
            }
        }
        
        // Check upper right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 1) {
                return false;
            }
        }
        
        return true;
    }
    
    // Recursive function to solve N-Queens
    bool solveNQueens(int row) {
        // Base case: all queens are placed
        if (row >= n) {
            return true;
        }
        
        // Try placing queen in each column of current row
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col)) {
                board[row][col] = 1; // Place queen
                
                // Recursively place queens in next rows
                if (solveNQueens(row + 1)) {
                    return true;
                }
                
                // Backtrack: remove queen if solution not found
                board[row][col] = 0;
            }
        }
        
        return false; // No solution found for this configuration
    }
    
    // Print the board
    void printSolution() {
        cout << "Solution for " << n << "-Queens:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 1) {
                    cout << "Q ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    
public:
    NQueens(int size) {
        n = size;
        board = vector<vector<int>>(n, vector<int>(n, 0));
    }
    
    void solve() {
        if (solveNQueens(0)) {
            printSolution();
        } else {
            cout << "No solution exists for " << n << "-Queens problem." << endl;
        }
    }
};

int main() {
    int n;
    
    cout << "Enter the number of queens (N): ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Please enter a positive number." << endl;
        return 1;
    }
    
    NQueens nqueens(n);
    nqueens.solve();
    
    return 0;
}
