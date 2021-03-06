#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <limits>
#include "..\include\Matrix.h"
#include "..\include\Tetramino.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

typedef vector<vector<char> > Vector2DChar;

int main()
{
  bool quit = false;
  char command[80];
  Matrix matrix;
  Vector2DChar matrixChars(HEIGHT, vector<char>(WIDTH, '.'));

  std::shared_ptr<Tetramino> activeTetramino;

  int score = 0;
  int linesCleared = 0;
  enum State { TITLE, PLAYING, PAUSED };
  State state = PLAYING;  // for the test suite, must start in PLAYING state

  do
  {
    cin.clear();
    cin.getline(command, 80);
    if (cin.fail())
    {
        cout << "Please enter fewer than 80 characters." << endl;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    for (unsigned int i = 0; i < strlen(command); ++i) {
      switch (command[i]) {
      case ' ':
        // do nothing
        // TODO: strip spaces first?
        break;
      case 'q':
        quit = true;
        goto quit;
        break;
      case '@':
        state = TITLE;
        break;
      case '!':
        switch (state) {
        case TITLE:
          state = PLAYING;
          break;
        case PAUSED:
          state = PLAYING;
          break;
        case PLAYING:
          state = PAUSED;
          break;
        }
        break;
      case 'p':
        switch (state) {
        case TITLE:
          matrix.printTitle();
          break;
        case PAUSED:
          matrix.printPause();
          break;
        case PLAYING:
          matrix.print();
          if (matrix.isGameOver()) {
            matrix.printGameOver();
          }
          break;
        }
        break;
      case 'P':
        matrix.printWithActive();
        if (matrix.isGameOver()) {
          matrix.printGameOver();
        }
        break;
      case 'g':
        char square;
        for (int i = 0; i < HEIGHT; ++i) {
          for (int j = 0; j < WIDTH; ++j) {
            cin >> square;
            matrixChars[i][j] = square;
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
        }
        else {
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
        matrix.spawnTetramino(command[i]);
        activeTetramino = matrix.getActiveTetramino();
        break;
      case ')':
        activeTetramino->rotate(Tetramino::Direction::CW, 90);
        break;
      case '(':
        activeTetramino->rotate(Tetramino::Direction::CCW, 90);
        break;
      case ';':
        cout << endl;
        break;
      case '<':
        matrix.nudgeActiveLeft();
        break;
      case '>':
        matrix.nudgeActiveRight();
        break;
      case 'v':
        matrix.nudgeActiveDown();
        break;
      case 'V':
        matrix.hardDrop();
        break;
      }
    }

  } while(!quit);

quit:
  return 0;
}
