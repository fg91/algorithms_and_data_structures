// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::flush;
using std::vector;

#define WIDTH 8

bool printBoard(vector<int> board) {
  if (board.size() != WIDTH) {
    return false;
  }
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (j == board[i]) {
        cout << "X " << flush;
      } else {
        cout << "- " << flush;
      }
    }
    cout << endl;
  }
  return true;
}

bool checkValid(vector<int> *board, int rownew, int colnew) {
  
  for (int rowold = 0; rowold < rownew; rowold++) {
    int colold = (*board)[rowold];
    // Check if rows have queen in same column
    if (colnew == colold) {
      return false;
    }
    // Check diagonals: distance between rows can't equal
    // distance between columns
    if (rownew - rowold == abs(colnew - colold)) {
      return false;
    }
  }
  return true;
}

void placeQueens(int row, vector<int> board, vector<vector<int> > *results) {
  if (row == WIDTH) {
    results->push_back(board);
  } else {
    for (int col = 0; col < WIDTH; col++) {
      if (checkValid(&board, row, col)) {
          board[row] = col;
          placeQueens(row + 1, board, results);
        }
    }
  }
}

int main() {

  vector<int> board(WIDTH);
  vector<vector<int> > results;
  placeQueens(0, board, &results);

  cout << results.size() << endl << endl;
  for (auto b : results) {
    printBoard(b);
    cout << endl;
  }


  return 0;
}
