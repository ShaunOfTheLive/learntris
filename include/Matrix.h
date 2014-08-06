#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
using std::vector;

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
    void print();
    void parse(Vector2DChar);
  protected:
  private:
    vector<vector<Colour> > matrix;

    void printCell(Colour);
};



#endif // MATRIX_H
