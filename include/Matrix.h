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
    static char colours[];

    void print();
    void parse(Vector2DChar);
    void clear();
  protected:
  private:
    Vector2DColour matrix;
    vector<char> matrixMap;

    void printCell(Colour);
};



#endif // MATRIX_H
