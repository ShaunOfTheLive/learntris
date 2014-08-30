#include <iostream>
#include <vector>
#include <string>
#include "Matrix.h"
#include "Tetramino.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

typedef vector<vector<char> > Vector2DChar;

void step();

int main()
{
  string command;
  Matrix matrix;
  Vector2DChar matrixChars(HEIGHT, vector<char>(WIDTH, '.'));

  Tetramino* activeTetramino = NULL;

  int score = 0;
  int linesCleared = 0;

  do
  {
    cin.clear();
    cin >> command;
    if (cin.fail())
    {
        cout << "Please enter a single character" << endl;
        cin.ignore(80, '\n');
    }

    switch (command[0]) {
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
      case '?':
        switch (command[1]) {
          case 's':
            cout << score << endl;
            break;
          case 'n':
            cout << linesCleared << endl;
            break;
        }
        break;
      case 's':
        matrix.step(score, linesCleared);
        break;
      case 't':
        if (activeTetramino) {
          activeTetramino->print();
        } else {
          cout << "ERROR!" << endl;
        }
        break;
      case 'S':
      case 'Z':
      case 'J':
      case 'T':
      case 'O':
      case 'I':
      case 'L':
        activeTetramino = new Tetramino(command[0]);
        break;
      case ')':
        activeTetramino->rotate();
        break;
      case ';':
        cout << endl;
        break;
    }
  } while(command[0] != 'q');

  return 0;
}
