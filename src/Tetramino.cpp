#include "../include/Tetramino.h"

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <ctype.h>

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
    row = 0;
    col = 0;
    width = tetraminoDefs[i].matrixSize[0];
    height = tetraminoDefs[i].matrixSize[1];
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

char Tetramino::cellToChar(Colour cell)
{
  char result;
  if (cell <= ORANGE) {
    result = colours[cell];
  }
  else {
    result = 'E';
  }
  return result;
}

void Tetramino::print() {
  Vector2DChar buffer(matrix.size(), vector<char>(matrix[0].size() * 2 - 1, ' '));
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0, k = 0; j < matrix[0].size(); ++j, k+=2) {
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

void Tetramino::blit(Vector2DChar& buffer, bool capital)
{
  for (size_t i = 0, r = row; i < matrix.size(); ++i, ++r) {
    for (size_t j = 0, c = col * 2; j < matrix[0].size(); ++j, c += 2) {
      buffer[r][c] = cellToChar(matrix[i][j]); // map i,j to rows and cols in buffer
      if (capital) {
        buffer[r][c] = toupper(buffer[r][c]);
      }
    }
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

void Tetramino::setRow(int row)
{
  this->row = row;
}

void Tetramino::setCol(int col)
{
  this->col = col;
}

int Tetramino::getRow()
{
  return row;
}

int Tetramino::getCol()
{
  return col;
}

int Tetramino::getWidth()
{
  return width;
}

int Tetramino::getHeight()
{
  return height;
}

void Tetramino::nudgeLeft()
{
  --col;
}

void Tetramino::nudgeRight()
{
  ++col;
}

void Tetramino::nudgeDown()
{
  ++row;
}

bool Tetramino::collidesHorz(int row)
{
  bool result = false;
  int innerRow = row - this->row;
  if (innerRow < 0 || innerRow >= height) {
    return false;
  }
  for (auto it = matrix[innerRow].begin(); it != matrix[innerRow].end(); ++it) {
    if (*it != EMPTY) {
      result = true;
    }
  }
  return result;
}

bool Tetramino::collidesVert(int col)
{
  bool result = false;
  int innerCol = col - this->col;
  if (innerCol < 0 || innerCol >= width) {
    return false;
  }
  for (auto it = matrix.begin(); it != matrix.end(); ++it) {
    if (it->at(innerCol) != EMPTY) {
      result = true;
    }
  }
  return result;
}
