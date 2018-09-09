#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <vector>
using std::vector;

#include "Tetramino.h"

typedef vector<vector<char> > Vector2DChar;

#define HEIGHT 22
#define WIDTH 10

class Matrix
{
  public:
    Matrix();
    virtual ~Matrix();

    enum Colour {EMPTY = 0, GREEN, RED, BLUE, MAGENTA, YELLOW, CYAN, ORANGE};
    typedef vector<vector<Colour> > Vector2DColour;
    static char colours[];
    std::shared_ptr<Tetramino> activeTetramino;

    void print();
    void printWithActive();
    void parse(Vector2DChar);
    void clear();
    void step(int &score, int &linesCleared);
    void spawnTetramino(char);
    void nudgeActiveLeft();
    void nudgeActiveRight();
    void nudgeActiveDown();
    void hardDrop();
    bool collidesWithSettled(std::shared_ptr<Tetramino>);
    std::shared_ptr<Tetramino> getActiveTetramino();
  protected:
  private:
    Vector2DColour matrix;
    vector<char> matrixMap;

    char cellToChar(Colour);
    static void printBuffer(Vector2DChar);
    void fossilizeTetramino(std::shared_ptr<Tetramino>);
};



#endif // MATRIX_H
