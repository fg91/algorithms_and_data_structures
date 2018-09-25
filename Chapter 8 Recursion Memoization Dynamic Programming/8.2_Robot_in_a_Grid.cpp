// "Copyright 2018 <Fabio M. Graetz>"
#include <unordered_set>
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_set;  // unordered_set on average has O(1) finding and inserting
using std::string;
using std::to_string;

//---------------------------------------//
//------------- Solution 1 --------------//
//---------------------------------------//

// Time complexity is O(2^(r+c)) where
// r is number of rows, c is number of columns
// because each path has r+c steps and at each
// step there are two possible options

bool getPath(vector<vector<bool> > *maze, int row, int column,
             vector<pair<int, int> > *path) {
  if (row < 0 || column < 0 || !(*maze)[row][column]) {
    return false;
  }

  bool isAtOrigin = (row == 0) && (column == 0);

  if (isAtOrigin || getPath(maze, row, column - 1, path)
      || getPath(maze, row - 1, column, path)) {
    path->push_back(make_pair(row, column));
    return true;
  }
  return false;
}

vector<pair<int, int> > getPath(vector<vector<bool> > maze) {
  if (maze.size() == 0 || maze[0].size() == 0) {
    return vector<pair<int, int> >();
  }
  vector<pair<int, int> > path;
  if (getPath(&maze, maze.size() - 1, maze[0].size() - 1, &path)) {
    return path;
  }
  return vector<pair<int, int> >();
}

//---------------------------------------//
//------------- Solution 2 --------------//
//------------- Memoization -------------//
//---------------------------------------//

// Time complexity O(r*c) since each cell is hit just once

bool getPathMemo(vector<vector<bool> > *maze,
                               int row, int column,
                               vector<pair<int, int> > *path,
                               unordered_set<string> *failedPoints) {
  if (row < 0 || column < 0 || !(*maze)[row][column]) {
    return false;
  }

  string point = to_string(row) + "-" + to_string(column);

  // If we have already visited this point, return false:
  if (failedPoints->count(point) == 1) {
    return false;
  }
  
  bool isAtOrigin = (row == 0) && (column == 0);

  // If there is a path from start to current location, add my location
  if (isAtOrigin || getPathMemo(maze, row, column - 1, path, failedPoints)
      || getPathMemo(maze, row - 1, column, path, failedPoints)) {
    path->push_back(make_pair(row, column));
    return true;
  }

  failedPoints->insert(point);
  return false;
}

vector<pair<int, int> > getPathMemo(vector<vector<bool> > maze) {
  if (maze.size() == 0 || maze[0].size() == 0) {
    return vector<pair<int, int> >();
  }
  vector<pair<int, int> > path;
  unordered_set<string> failedPoints;
  
  if (getPathMemo(&maze, maze.size() - 1, maze[0].size() - 1, &path, &failedPoints)) {
    return path;
  }
  return vector<pair<int, int> >();
}

int main() {
  vector<vector<bool> > maze{
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1}
  };

  auto path = getPath(maze);
  auto path2 = getPathMemo(maze);
  for (vector<pair<int, int> >::iterator it = path.begin(); it != path.end(); it++) {
    cout << "(" << (*it).first <<"," << (*it).second << ")" << endl;
  }
  cout << endl;
  for (vector<pair<int, int> >::iterator it = path2.begin(); it != path2.end(); it++) {
    cout << "(" << (*it).first <<"," << (*it).second << ")" << endl;
  }
  
  return 0;
}
