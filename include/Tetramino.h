#ifndef TETRAMINO_H
#define TETRAMINO_H

#include <vector>
#include <utility>

using std::vector;
using std::pair;

#define NUM_TETRAS 7

typedef vector<vector<char> > Vector2DChar;

class Tetramino
{
  public:
    Tetramino(char name);
    virtual ~Tetramino();

    enum Colour {EMPTY = 0, GREEN, RED, BLUE, MAGENTA, YELLOW, CYAN, ORANGE};
    enum Direction {CW = 0, CCW};
    struct tetraminoDef {
      char name;
      Colour colour;
      int matrixSize[2];
      int coords[4][2];
    };
    typedef vector<vector<Colour> > Vector2DColour;
    static tetraminoDef tetraminoDefs[NUM_TETRAS];

    static char colours[];

    int row;
    int col;
    int width;
    int height;

    bool settled;

    void print();
    void blit(Vector2DChar&, bool capital = false);
    void rotate(Direction dir = CW, int angle = 90);
//    static tetraminoDefs[] defineTetraminos();
    void setRow(int);
    void setCol(int);
    int getRow();
    int getCol();
    int getWidth();
    int getHeight();
    void nudgeLeft();
    void nudgeRight();
    void nudgeDown();
    void nudgeUp();
    bool collidesHorz(int);
    bool collidesVert(int);
    bool isSettled();
    void setSettled();
    
    Vector2DColour getMatrix();
  protected:
  private:
    char name;
    Colour colour;
    Vector2DColour matrix;

    char cellToChar(Colour);
};

#endif // TETRAMINO_H
