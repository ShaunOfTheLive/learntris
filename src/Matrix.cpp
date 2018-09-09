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

void Matrix::printBuffer(Vector2DChar buffer) {
  for (size_t i = 0; i < buffer.size(); ++i) {
    for (size_t j = 0; j < buffer[0].size(); ++j) {
      cout << buffer[i][j];
    }
    cout << endl;
  }
}

void Matrix::fossilizeTetramino(std::shared_ptr<Tetramino> tetramino)
{
  Tetramino::Vector2DColour tMatrix = tetramino->getMatrix();
  int tRow = tetramino->getRow();
  int tCol = tetramino->getCol();
  for (size_t i = 0; i < tMatrix.size(); ++i) {
    for (size_t j = 0; j < tMatrix[i].size(); ++j) {
      if (tRow+i >= 0 && tRow+i < matrix.size() && tCol+i >=0 && tCol+i < matrix[tRow+i].size()) {
        if (tMatrix[i][j] != EMPTY) {
          matrix[tRow + i][tCol + j] = (Matrix::Colour)tMatrix[i][j];
        }
      }
    }
  }
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
  printBuffer(buffer);
}

void Matrix::printWithActive() {
  Vector2DChar buffer(matrix.size(), vector<char>(matrix[0].size() * 2 - 1, ' '));
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0, k = 0; j < matrix[0].size(); ++j, k += 2) {
      buffer[i][k] = cellToChar(matrix[i][j]);
    }
  }
  if (activeTetramino) {
    activeTetramino->blit(buffer, true);
  }
  printBuffer(buffer);
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

void Matrix::spawnTetramino(char name)
{
  if (activeTetramino && !activeTetramino->isSettled()) {
    // TODO: exception? can't spawn another active tetramino until the current one is settled
  }
  else {
    activeTetramino = std::shared_ptr<Tetramino>(new Tetramino(name));
    if (name == 'O') {
      activeTetramino->setCol(4);
    }
    else {
      activeTetramino->setCol(3);
    }
  }
}

void Matrix::nudgeActiveLeft()
{
  if (activeTetramino) {
    activeTetramino->nudgeLeft();
    if (activeTetramino->collidesVert(-1) || collidesWithSettled(activeTetramino)) {
      activeTetramino->nudgeRight();
    }
  }
}

void Matrix::nudgeActiveRight()
{
  if (activeTetramino) {
    activeTetramino->nudgeRight();
    if (activeTetramino->collidesVert(WIDTH) || collidesWithSettled(activeTetramino)) {
      activeTetramino->nudgeLeft();
    }
  }
}

void Matrix::nudgeActiveDown()
{
  if (activeTetramino) {
    activeTetramino->nudgeDown();
    if (activeTetramino->collidesHorz(HEIGHT) || collidesWithSettled(activeTetramino)) {
      activeTetramino->nudgeUp();
      fossilizeTetramino(activeTetramino);
      // activeTetramino = nullptr;
      activeTetramino->setSettled();
    }
  }
}

void Matrix::hardDrop()
{
  for (int i = 0; i < HEIGHT; ++i) {
    nudgeActiveDown();
  }
}

bool Matrix::collidesWithSettled(std::shared_ptr<Tetramino> tetramino)
{
  bool result = false;

  Tetramino::Vector2DColour tMatrix = tetramino->getMatrix();
  int tRow = tetramino->getRow();
  int tCol = tetramino->getCol();
  for (size_t i = 0; i < tMatrix.size(); ++i) {
    for (size_t j = 0; j < tMatrix[i].size(); ++j) {
      if (tRow + i >= 0 && tRow + i < matrix.size() && tCol + j >= 0 && tCol + j < matrix[tRow + i].size()) {
        //matrix[tRow + i][tCol + j] = (Matrix::Colour)tMatrix[i][j];
        if (matrix[tRow + i][tCol + j] != EMPTY && tMatrix[i][j] != EMPTY) {
          result = true;
          goto end;
        }
      }
    }
  }

end:
  return result;
}

std::shared_ptr<Tetramino> Matrix::getActiveTetramino()
{
  return activeTetramino;
}
