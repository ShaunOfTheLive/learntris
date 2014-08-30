#include "Tetramino.h"

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;

char Tetramino::colours[] = {'.', 'g', 'r', 'b', 'm', 'y', 'c', 'o'};

Tetramino::Tetramino(char name)
{
  int i = 0;

  for (i = 0; i < NUM_TETRAS; ++i) {
    if (tetraminoDefs[i].name == name) {
      break;
    }
  }

  if (i == NUM_TETRAS) {
    // TODO: throw exception
  } else {
    name = tetraminoDefs[i].name;
    colour = tetraminoDefs[i].colour;
    int width = tetraminoDefs[i].matrixSize[0];
    int height = tetraminoDefs[i].matrixSize[1];
    matrix = Vector2DColour(width, vector<Colour>(height, EMPTY));

    for (int j = 0; j < 4; ++j) {
      int x = tetraminoDefs[i].coords[j][0];
      int y = tetraminoDefs[i].coords[j][1];
      matrix[x][y] = colour;
    }
  }
}

Tetramino::~Tetramino()
{
  //dtor
}

Tetramino::tetraminoDef Tetramino::tetraminoDefs[NUM_TETRAS] = {
  {'S', GREEN,   {3,3}, {{0,1},{0,2},{1,0},{1,1}}},
  {'Z', RED,     {3,3}, {{0,0},{0,1},{1,1},{1,2}}},
  {'J', BLUE,    {3,3}, {{0,0},{1,0},{1,1},{1,2}}},
  {'T', MAGENTA, {3,3}, {{0,1},{1,0},{1,1},{1,2}}},
  {'O', YELLOW,  {2,2}, {{0,0},{0,1},{1,0},{1,1}}},
  {'I', CYAN,    {4,4}, {{1,0},{1,1},{1,2},{1,3}}},
  {'L', ORANGE,  {3,3}, {{0,2},{1,0},{1,1},{1,2}}}
};

void Tetramino::printCell(Colour cell) {
  if (cell <= ORANGE) {
    cout << colours[cell];
  } else {
    cout << "E";
  }
}

void Tetramino::print() {
  for (size_t i = 0; i < matrix.size(); ++i) {
    printCell(matrix[i][0]);
    for (size_t j = 1; j < matrix[0].size(); ++j) {
      cout << " ";
      printCell(matrix[i][j]);
    }
    cout << endl;
  }
}

void Tetramino::rotate(Direction dir, int angle) {
  // just do 90 CW right now for testing

  // this algorithm is only designed for rotating square matrices
  int size = matrix.size();

  Vector2DColour newMatrix(size, vector<Colour>(size, EMPTY));

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      newMatrix[j][size - 1 - i] = matrix[i][j];
    }
  }

  matrix = newMatrix;
}
