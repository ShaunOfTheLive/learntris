#include "../include/Matrix.h"

#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::find;
#include <iterator>
using std::distance;

char Matrix::colours[] = {'.', 'g', 'r', 'b', 'm', 'y', 'c', 'o'};

Matrix::Matrix(): matrix(HEIGHT, vector<Colour>(WIDTH, EMPTY))
{

  matrixMap = vector<char>(colours, colours + sizeof(colours) / sizeof(char));
}

Matrix::~Matrix()
{
  //dtor
}

char Matrix::cellToChar(Colour cell) {
  char result;
  if (cell <= ORANGE) {
    result = colours[cell];
  }
  else {
    result = 'E';
  }
  return result;
}

void Matrix::print() {
  Vector2DChar buffer(matrix.size(), vector<char>(matrix[0].size() * 2 - 1, ' '));
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0, k = 0; j < matrix[0].size(); ++j, k += 2) {
      buffer[i][k] = cellToChar(matrix[i][j]);
    }
  }
  for (size_t i = 0; i < buffer.size(); ++i) {
    for (size_t j = 0; j < buffer[0].size(); ++j) {
      cout << buffer[i][j];
    }
    cout << endl;
  }
}

void Matrix::parse(Vector2DChar matrix)
{
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0; j < matrix[0].size(); ++j) {
      //read in matrix[i][j], look it up in matrixMap, assign that to Matrix::matrix[i][j]
      //TODO: rename member variable to m_matrix
      vector<char>::iterator it = find(matrixMap.begin(), matrixMap.end(), matrix[i][j]);
      if (it == matrixMap.end()) {
        cout << "ERROR" << endl;
      }
      int dist = distance(matrixMap.begin(), find(matrixMap.begin(), matrixMap.end(), matrix[i][j]));
      if (dist != 0) {
        //cout << dist << endl;
      }
      Matrix::matrix[i][j] = (Colour)distance(matrixMap.begin(), find(matrixMap.begin(), matrixMap.end(), matrix[i][j]));
    }
  }
}

void Matrix::clear()
{
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0; j < matrix[0].size(); ++j) {
      matrix[i][j] = EMPTY;
    }
  }
}

void Matrix::step(int &score, int &linesCleared)
{
  for (size_t i = 0; i < matrix.size(); ++i) {
    // if an empty cell is not found in the row
    if (find(matrix[i].begin(), matrix[i].end(), EMPTY) == matrix[i].end()) {
      fill(matrix[i].begin(), matrix[i].end(), EMPTY);
      score += 100;
      linesCleared += 1;
    }
  }
}
