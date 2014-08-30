#ifndef TETRAMINO_H
#define TETRAMINO_H

#include <vector>
#include <utility>

using std::vector;
using std::pair;

#define NUM_TETRAS 7

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

    void print();
    void rotate(Direction dir = CW, int angle = 90);
//    static tetraminoDefs[] defineTetraminos();
  protected:
  private:
    char name;
    Colour colour;
    Vector2DColour matrix;

    void printCell(Colour);
};

#endif // TETRAMINO_H
