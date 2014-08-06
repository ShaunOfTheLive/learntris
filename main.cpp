#include <iostream>
#include <vector>
#include "Matrix.h"

//TODO: change switch to handle multi-character strings
//        "?s" is a valid input

using namespace std;

typedef vector<vector<char> > Vector2DChar;

int main()
{
  char command;
  Matrix matrix;
  Vector2DChar matrixChars(HEIGHT, vector<char>(WIDTH, '.'));

  int score;

  do
  {
    cin.clear();
    cin >> command;
    if (cin.fail())
    {
        cout << "Please enter a single character" << endl;
        cin.ignore(80, '\n');
    }

    switch (command) {
      case 'q':
        //quit
        break;
      case 'p':
        matrix.print();
        break;
      case 'g':
        char square;
        for (int i = 0; i < HEIGHT; ++i) {
          for (int j = 0; j < WIDTH; ++j) {
            cin >> square;
            //debug
            if (square == 'Q') {
              j = WIDTH;
              i = HEIGHT;
              break;
            }
            matrixChars[i][j] = square;
            //matrix.parse(matrixChars);
          }
        }
        matrix.parse(matrixChars);
        break;
      case 'c':
        matrix.clear();
        break;
    }
  } while(command != 'q');

  return 0;
}
