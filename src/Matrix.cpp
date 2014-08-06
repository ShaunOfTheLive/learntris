#include "Matrix.h"

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

//TODO: put this in a namespace or something
void Matrix::printCell(Colour cell) {
  if (cell <= ORANGE) {
    cout << colours[cell];
  } else {
    cout << "E";
  }
}

void Matrix::print() {
  for (int i = 0; i < matrix.size(); ++i) {
    printCell(matrix[i][0]);
    for (int j = 1; j < matrix[0].size(); ++j) {
      cout << " ";
      printCell(matrix[i][j]);
    }
    cout << endl;
  }
}

void Matrix::parse(Vector2DChar matrix)
{
    for (int i = 0; i < matrix.size(); ++i) {
      for (int j = 0; j < matrix[0].size(); ++j) {
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
