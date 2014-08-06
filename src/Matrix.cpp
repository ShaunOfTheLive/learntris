#include "Matrix.h"

#include <iostream>
using std::cout;
using std::endl;

Matrix::Matrix(): matrix(HEIGHT, vector<Colour>(WIDTH, EMPTY))
{
  //ctor
}

Matrix::~Matrix()
{
  //dtor
}

//TODO: put this in a namespace or something
void Matrix::printCell(Colour cell) {
  if (cell == 0) {
    cout << ".";
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

}
